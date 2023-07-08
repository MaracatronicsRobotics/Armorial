#include <Armorial/Threaded/EntityManager/EntityManager.h>

using namespace Threaded;

void EntityManager::addEntity(Entity* entity, int entityPriority) {
    _priorityMap.insert(entityPriority, entity);
}

void EntityManager::startEntities() {
    // Get keys (priorities) sorted by low to high
    QList<int> priorities = _priorityMap.keys();

    // Sort keys from high to low
    std::sort(priorities.begin(), priorities.end(), [](const int &v1, const int &v2) { return v1 > v2; });

    // Iterate from the high priorities to low priorities
    QList<int>::iterator it;
    for(it = priorities.begin(); it != priorities.end(); it++) {
        // Get Entities by priority
        QList<Entity*> entities = _priorityMap.values((*it));

        // Start entities
        QList<Entity*>::iterator it2;
        for(it2 = entities.begin(); it2 != entities.end(); it2++) {
            Entity *entity = (*it2);
            entity->start();
        }
    }
}

void EntityManager::disableEntities() {
    // Get keys (priorities) already sorted by low to high
    QList<int> priorities = _priorityMap.keys();

    // Iterate from the low priorities to high priorities
    QList<int>::iterator it;
    for(it = priorities.begin(); it != priorities.end(); it++) {
        // Get Entities by priority
        QList<Entity*> entities = _priorityMap.values((*it));

        // Finish and wait
        QList<Entity*>::iterator it2;
        for(it2 = entities.begin(); it2 != entities.end(); it2++) {
            Entity *entity = (*it2);

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

QList<Entity*> EntityManager::getEntities() {
    return _priorityMap.values();
}
