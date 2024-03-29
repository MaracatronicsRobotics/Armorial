﻿#include <Armorial/Geometry/Vector2D/Vector2D.h>

#include <Armorial/Utils/Utils.h>

#include <assert.h>
#include <math.h>

using namespace Geometry;

Vector2D::Vector2D(const float &x, const float &y) {
    _x = x;
    _y = y;
}

Vector2D::Vector2D(const Angle &angle, const float &length) {
    _x = cos(angle.value()) * length;
    _y = sin(angle.value()) * length;
}

float Vector2D::x() const {
    return _x;
}

float Vector2D::y() const {
    return _y;
}

float Vector2D::dotProduct(const Vector2D &other) const {
    return (_x * other._x + _y * other._y);
}

float Vector2D::dist(const Vector2D &other) const {
    return (*this - other).length();
}

Vector2D Vector2D::scale(const float &scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

Vector2D Vector2D::normalize() const {
    if(Utils::Compare::isEqual(this->length(), 0.0f)) return Vector2D(0.0f, 0.0f);

    float d = 1.0 / length();
    return Vector2D(_x * d, _y * d);
}

float Vector2D::length() const {
    return sqrt(length2());
}

float Vector2D::length2() const {
    return (_x * _x + _y * _y);
}

float Vector2D::angle() const {
    return this->toAngle().value();
}

Geometry::Angle Vector2D::toAngle() const {
    return Geometry::Angle(atan2(_y, _x));
}

Vector2D Vector2D::lerp(const Vector2D &other, const float &factor) const {
    return (this->scale(factor) + other.scale(1 - factor));
}

Vector2D Vector2D::rotate(const float &radians) const {
    float c = cos(radians);
    float s = sin(radians);

    return Vector2D(_x * c - _y * s, _x * s + _y * c);
}

Vector2D Vector2D::rotateAroundPoint(const float &radians, const Vector2D &pivot) const {
    float c = cos(radians);
    float s = sin(radians);

    // Calculate new position
    float rotatedX = (_x - pivot._x) * c - (_y - pivot._y) * s + pivot._x;
    float rotatedY = (_x - pivot._y) * s + (_y - pivot._y) * c + pivot._y;

    return Vector2D(rotatedX, rotatedY);
}

Vector2D Vector2D::project(const Vector2D &other) const {
    return other.scale(this->dotProduct(other) / other.dotProduct(other));
}

Vector2D Vector2D::project(const Vector2D &line_a, const Vector2D &line_b) const {
    Vector2D ab = line_b - line_a;
    Vector2D ap = (*this) - line_a;

    float t = ap.dotProduct(ab) / ab.dotProduct(ab);
    if(t < 0.0) {
        return line_a;
    }
    else if(t > 1.0) {
        return line_b;
    }

    return line_a + ab.scale(t);
}

bool Vector2D::isValid() const {
    // NaN is not equal to itself
    return Utils::Compare::isEqual(_x, _x) && Utils::Compare::isEqual(_y, _y);
}

float Vector2D::crossProductMagnitude(const Vector2D &other) const {
    return std::fabs(_x * other._y - _y * other._x);
}

Vector2D Vector2D::stretchToLength(const float &targetLength) const {
    if(Utils::Compare::isEqual(length(), 0.0f)) {
        return Vector2D(0.0f, 0.0f);
    }

    float frac = targetLength / length();
    return Vector2D(_x * frac, _y * frac);
}

bool Vector2D::operator==(const Vector2D &other) const {
    return fabs(this->_x - other._x) < 1e-4 && fabs(this->_y - other._y) < 1e-4;
}

bool Vector2D::operator!=(const Vector2D &other) const {
    return !(*this == other);
}

bool Vector2D::operator<(const Vector2D &other) const {
    return this->length() < other.length();
}

Vector2D Vector2D::operator+=(const Vector2D &other) {
    return Vector2D(this->_x += other._x, this->_y += other._y);
}

Vector2D Vector2D::operator+=(const float &scalar) {
    return Vector2D(_x += scalar, _y += scalar);
}

Vector2D Vector2D::operator-=(const Vector2D &other) {
    return Vector2D(_x -= other._x, _y -= other._y);
}

Vector2D Vector2D::operator-=(const float &scalar) {
    return Vector2D(_x -= scalar, _y -= scalar);
}

Vector2D Vector2D::operator*=(const Vector2D &other) {
    return Vector2D(_x *= other._x, _y *= other._y);
}

Vector2D Vector2D::operator*=(const float &scalar) {
    return Vector2D(_x *= scalar, _y *= scalar);
}

Vector2D Vector2D::operator/=(const Vector2D &other) {
    assert(!(other == Vector2D()) && "Division by zero");
    return Vector2D(_x /= other._x, _y /= other._y);
}

Vector2D Vector2D::operator/=(const float &scalar) {
    return Vector2D(_x /= scalar, _y /= scalar);
}

Vector2D Vector2D::operator+(const Vector2D &other) const {
    return Vector2D(_x + other._x, _y + other._y);
}

Vector2D Vector2D::operator+(const float &scalar) const {
    return Vector2D(_x + scalar, _y + scalar);
}

Vector2D Vector2D::operator-(const Vector2D &other) const {
    return Vector2D(_x - other._x, _y - other._y);
}

Vector2D Vector2D::operator-(const float &scalar) const {
    return Vector2D(_x - scalar, _y - scalar);
}

Vector2D Vector2D::operator*(const Vector2D &other) const {
    return Vector2D(_x * other._x, _y * other._y);
}

Vector2D Vector2D::operator*(const float &scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

Vector2D Vector2D::operator/(const Vector2D &other) const {
    return Vector2D(_x / other._x, _y / other._y);
}

Vector2D Vector2D::operator/(const float &scalar) const {
    return Vector2D(_x / scalar, _y / scalar);
}

QString Vector2D::toQString() {
    return QString("(%1, %2)").arg(_x).arg(_y);
}

std::string Vector2D::toStdString() {
    return toQString().toStdString();
}
