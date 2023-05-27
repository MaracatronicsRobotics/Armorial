#include <Armorial/Threaded/Entity/Entity.h>

#include <chrono>
#include <spdlog/spdlog.h>

using namespace Threaded;

Entity::Entity() {
    setLoopFrequency(60);
    _isEnabled = true;
    _isStopped = false;
    _currentFPS = 0.0f;
}

void Entity::setLoopFrequency(const quint16 hz) {
    _entityMutex.lock();
    _loopFrequency = hz;
    _entityMutex.unlock();
}

void Entity::enableEntity() {
    _entityMutex.lock();

    // If Entity is already enabled, check if it is stopped
    // and remove stopped status if True.
    if(_isEnabled) {
        if(_isStopped) _isStopped = false;
    }
    // Otherwise, the entity is not enabled, so enable it and mark
    // stopped status as False.
    else {
        _isEnabled = true;
        _isStopped = false;
    }

    _entityMutex.unlock();
}

void Entity::disableEntity() {
    _entityMutex.lock();
    _isEnabled = false;
    _entityMutex.unlock();
}

void Entity::stopEntity() {
    _entityMutex.lock();
    _isStopped = true;
    _entityMutex.unlock();
}

quint16 Entity::loopFrequency() {
    _entityMutex.lock();
    quint16 loopFrequency = _loopFrequency;
    _entityMutex.unlock();

    return loopFrequency;
}

bool Entity::isEnabled() {
    _entityMutex.lock();
    bool enabled = _isEnabled;
    _entityMutex.unlock();

    return enabled;
}

bool Entity::isStopped() {
    _entityMutex.lock();
    bool stopped = _isStopped;
    _entityMutex.unlock();

    return stopped;
}

void Entity::run() {
    // Cast initialization() virtual children implementation
    initialization();

    // While Entity is enabled (remember that enabled status != stopped status)
    while(isEnabled()) {
        // Start timer
        startTimer();

        // If Entity is not stopped, cast loop() implementation
        if(!isStopped()) {
            loop();
        }

        // Take the remaining time from the loop cast
        long rest = getRemainingTime();

        // If rest is positive, it is, the loop has succesfully run in the desired time
        // put the Entity to sleep for the remaining time.
        if(rest >= 0) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(rest));
        }
        // Else, if the rest is negative, it means that the loop call has achieved a duration
        // that is higher than the expected by the desired frequency, so alert the user.
        else {
            spdlog::warn("[{}] Entity timer overextended for {} milliseconds.", entityName().toStdString(), -rest);
        }

        // Set the current FPS for this Entity instance
        setFPS(1000.0f / getDeltaTime());
    }

    // When the Entity is disabled, it leaves the while, so cast the finalization() implementation
    finalization();
}

void Entity::startTimer() {
    // Call start implementation from timer
    _entityTimer.start();
}

long Entity::getRemainingTime() {
    // Get the remaining time (in milliseconds) based on the desired frequency
    long remainingTime = ((1000.0f / loopFrequency()) - _entityTimer.getMilliseconds())*1E6;

    return remainingTime;
}

float Entity::getDeltaTime() {
    return _entityTimer.getMilliseconds();
}

float Entity::getFPS() {
    _entityMutex.lock();
    float currentFPS = _currentFPS;
    _entityMutex.unlock();

    return currentFPS;
}

void Entity::setFPS(const float &fps) {
    _entityMutex.lock();
    _currentFPS = fps;
    _entityMutex.unlock();
}
