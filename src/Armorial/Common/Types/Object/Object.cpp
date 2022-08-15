#include <Armorial/Common/Types/Object/Object.h>

using namespace Common::Types;

Object::Object(const Geometry::Vector2D &position, const Geometry::Angle &orientation, const quint8 identifier) {
    _position = position;
    _velocity = Geometry::Vector2D();
    _acceleration = Geometry::Vector2D();
    _orientation = orientation;
    _identifier = identifier;
}

void Object::setPosition(const Geometry::Vector2D &position) {
    _dataMutex.lockForWrite();
    _position = position;
    _dataMutex.unlock();
}

Geometry::Vector2D Object::getPosition() {
    _dataMutex.lockForRead();
    Geometry::Vector2D position = _position;
    _dataMutex.unlock();

    return position;
}

void Object::setVelocity(const Geometry::Vector2D &velocity) {
    _dataMutex.lockForWrite();
    _velocity = velocity;
    _dataMutex.unlock();
}

Geometry::Vector2D Object::getVelocity() {
    _dataMutex.lockForRead();
    Geometry::Vector2D velocity = _velocity;
    _dataMutex.unlock();

    return velocity;
}

void Object::setAcceleration(const Geometry::Vector2D &acceleration) {
    _dataMutex.lockForWrite();
    _acceleration = acceleration;
    _dataMutex.unlock();
}

Geometry::Vector2D Object::getAcceleration() {
    _dataMutex.lockForRead();
    Geometry::Vector2D acceleration = _acceleration;
    _dataMutex.unlock();

    return acceleration;
}

void Object::setOrientation(const Geometry::Angle &orientation) {
    _dataMutex.lockForWrite();
    _orientation = orientation;
    _dataMutex.unlock();
}

Geometry::Angle Object::getOrientation() {
    _dataMutex.lockForRead();
    Geometry::Angle orientation = _orientation;
    _dataMutex.unlock();

    return orientation;
}

void Object::setIdentifier(const quint8 &identifier) {
    _dataMutex.lockForWrite();
    _identifier = identifier;
    _dataMutex.unlock();
}

quint8 Object::getIdentifier() {
    _dataMutex.lockForRead();
    quint8 identifier = _identifier;
    _dataMutex.unlock();

    return identifier;
}
