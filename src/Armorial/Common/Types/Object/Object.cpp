#include <Armorial/Common/Types/Object/Object.h>

using namespace Common::Types;

Object::Object(const Object &another) {
  setPosition(another.getPosition());
  setVelocity(another.getVelocity());
  setAcceleration(another.getAcceleration());
  setOrientation(another.getOrientation());
  setAngularSpeed(another.getAngularSpeed());
}

Object::Object(const Geometry::Vector2D &position,
               const Geometry::Vector2D &velocity,
               const Geometry::Vector2D &acceleration,
               const Geometry::Angle &orientation, const float &angularSpeed) {
  setPosition(position);
  setVelocity(velocity);
  setAcceleration(acceleration);
  setOrientation(orientation);
  setAngularSpeed(angularSpeed);
}

float Object::distTo(const Geometry::Vector2D &position) {
  _mutex.lockForRead();
  Geometry::Vector2D objPosition = _position;
  _mutex.unlock();

  return objPosition.dist(position);
}

Geometry::Vector2D Object::getPosition() const {
  _mutex.lockForRead();
  Geometry::Vector2D position = _position;
  _mutex.unlock();

  return position;
}

Geometry::Vector2D Object::getVelocity() const {
  _mutex.lockForRead();
  Geometry::Vector2D velocity = _velocity;
  _mutex.unlock();

  return velocity;
}

Geometry::Vector2D Object::getAcceleration() const {
  _mutex.lockForRead();
  Geometry::Vector2D acceleration = _acceleration;
  _mutex.unlock();

  return acceleration;
}

Geometry::Angle Object::getOrientation() const {
  _mutex.lockForRead();
  Geometry::Angle orientation = _orientation;
  _mutex.unlock();

  return orientation;
}

float Object::getAngularSpeed() const {
  _mutex.lockForRead();
  float angularSpeed = _angularSpeed;
  _mutex.unlock();

  return angularSpeed;
}

void Object::setPosition(const Geometry::Vector2D &position) {
  _mutex.lockForWrite();
  _position = position;
  _mutex.unlock();
}

void Object::setVelocity(const Geometry::Vector2D &velocity) {
  _mutex.lockForWrite();
  _velocity = velocity;
  _mutex.unlock();
}

void Object::setAcceleration(const Geometry::Vector2D &acceleration) {
  _mutex.lockForWrite();
  _acceleration = acceleration;
  _mutex.unlock();
}

void Object::setOrientation(const Geometry::Angle &orientation) {
  _mutex.lockForWrite();
  _orientation = orientation;
  _mutex.unlock();
}

void Object::setAngularSpeed(const float &angularSpeed) {
  _mutex.lockForWrite();
  _angularSpeed = angularSpeed;
  _mutex.unlock();
}

Object &Object::operator=(const Object &another) {
  this->setPosition(another.getPosition());
  this->setVelocity(another.getVelocity());
  this->setOrientation(another.getOrientation());
  this->setAcceleration(another.getAcceleration());
  this->setAngularSpeed(another.getAngularSpeed());

  return *this;
}
