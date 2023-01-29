#include "EntityCommons.h"

using namespace EntityCommons;

/*
 *  Entidade Class
 *
*/

Entidade::Entidade() {
    _curStatus = QString("Created");
    _valueCheck = 1;
    _autoEnd = 0;
}

Entidade::~Entidade() {}

QString Entidade::getStatus() {
    return _curStatus;
}

int Entidade::getValueCheck() {
    return _valueCheck;
}

void Entidade::toInit() {
    initialization();
}

void Entidade::toLoop() {
    loop();
}

void Entidade::toEnd() {
    finalization();
}

void Entidade::toRun() {
    run();
}

void Entidade::increaseIt(int val) {
    _entityMutex.tryLock();
    _autoEnd = val + 10;
    _entityMutex.unlock();
}

void Entidade::run() {
    // Cast initialization() virtual children implementation
    initialization();

    // While Entity is enabled (remember that enabled status != stopped status)
    while(isEnabled()) {
        // Start timer
        startTimer();

        // If Entity is not stopped, cast loop() implementation
        if(!isStopped()) {
            loop();
            stopEntity();
            disableEntity();
        }

        // Take the remaining time from the loop cast
        long rest = getRemainingTime();

        // If rest is positive, it is, the loop has succesfully run in the desired time
        // put the Entity to sleep for the remaining time.
        if(rest >= 0) {
            msleep(rest);
        }
        // Else, if the rest is negative, it means that the loop call has achieved a duration
        // that is higher than the expected by the desired frequency, so alert the user.
        else {
            spdlog::warn("[{}] Entity timer overextended for {} milliseconds.", entityName().toStdString(), -rest);
        }
    }

    // When the Entity is disabled, it leaves the while, so cast the finalization() implementation
    finalization();
}

void Entidade::initialization() {
    _curStatus = QString("Initialized");
    _valueCheck = 2;
    increaseIt(_autoEnd);
}

void Entidade::loop() {
    _curStatus = QString("In Loop");
    _valueCheck = 3;
    increaseIt(_autoEnd);
    if (_autoEnd >= 5) {
        stopEntity();
        disableEntity();
    }
}

void Entidade::finalization() {
    _curStatus = QString("Finalized");
    _valueCheck = 4;
}

void Entidade::startTimer() {
    // Call start implementation from timer
    _entityTimer.start();
}


long Entidade::getRemainingTime() {
    // Get the remaining time (in milliseconds) based on the desired frequency
    long remainingTime = (1000 / loopFrequency()) - _entityTimer.getMilliseconds();

    return remainingTime;
}

/*
 *  Teste Class
 *
*/

Teste::Teste() {
}

/*
 *  Another Teste Class
 *
*/

Teste2::Teste2() {
}

/*
 *  ManagerMockable Class
 *
*/

void ManagerMockable::addEntity(EntityMock *entity, int entityPriority) {
    _priorityMap.insert(entityPriority, entity);
}

void ManagerMockable::startEntities() {
    QList<int> priorities = _priorityMap.keys();

    // Sort keys from high to low
    std::sort(priorities.begin(), priorities.end(), [](const int &v1, const int &v2) { return v1 > v2; });

    // Iterate from the high priorities to low priorities
    QList<int>::iterator it;
    for(it = priorities.begin(); it != priorities.end(); it++) {
        // Get Entities by priority
        QList<EntityMock*> entities = _priorityMap.values((*it));

        // Start entities
        QList<EntityMock*>::iterator it2;
        for(it2 = entities.begin(); it2 != entities.end(); it2++) {
            EntityMock *entity = (*it2);
            entity->start();
        }
    }
}

void ManagerMockable::disableEntities() {
    QList<int> priorities = _priorityMap.keys();

    // Iterate from the low priorities to high priorities
    QList<int>::iterator it;
    for(it = priorities.begin(); it != priorities.end(); it++) {
        // Get Entities by priority
        QList<EntityMock*> entities = _priorityMap.values((*it));

        // Finish and wait
        QList<EntityMock*>::iterator it2;
        for(it2 = entities.begin(); it2 != entities.end(); it2++) {
            EntityMock *entity = (*it2);

            // Disable and wait
            entity->disableEntity();
            entity->wait();

            // Remove from map
            _priorityMap.remove((*it), (*it2));

            // Delete
            delete entity;
        }
    }
}
