#include <Armorial/Geometry/Angle/Angle.h>

#include <math.h>

using namespace Geometry;

Angle::Angle(const float &angle) {
    _angle = angle;
    normalize();
}

float Angle::value() const {
    return _angle;
}

Angle Angle::normalize() {
    _angle = fmod(value() + M_PI, 2.0 * M_PI);
    _angle = (value() <= 0.0) ? value() + M_PI : value() - M_PI;

    return *this;
}

Angle::Direction Angle::rotateDirection(const Angle &target) const {
    float angleDiff = target.value() - this->value();
    bool positive = (angleDiff >= 0.0);
    bool large = fabs(angleDiff) >= M_PI;

    return Angle::Direction(positive ^ large);
}

float Angle::shortestAngleDiff(const Angle &target) const {
    float thisToOther = fabs((*this - target).value());
    float otherToThis = fabs((target - *this).value());
    return std::min(thisToOther, otherToThis);
}

bool Angle::operator==(const Angle &other) const {
    return this->shortestAngleDiff(other) < 1e-4;
}

bool Angle::operator!=(const Angle &other) const {
    return !(*this == other);
}

Angle Angle::operator+(const Angle &other) const {
    return Angle(this->value() + other.value());
}

Angle Angle::operator-(const Angle &other) const {
    return Angle(this->value() - other.value());
}

Angle &Angle::operator+=(const Angle &other) {
    this->_angle += other.value();
    this->normalize();
    return *this;
}

Angle &Angle::operator-=(const Angle &other) {
    this->_angle -= other.value();
    this->normalize();
    return *this;
}

Angle &Angle::operator=(const float &scalar) {
    this->_angle = scalar;
    this->normalize();
    return *this;
}
