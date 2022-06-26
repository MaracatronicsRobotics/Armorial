#include <Armorial/Geometry/Vector2D/Vector2D.h>

#include <assert.h>
#include <math.h>

namespace Geometry {

Vector2D::Vector2D(const double x, const double y) {
    _x = x;
    _y = y;
}

Vector2D::Vector2D(Types::Angle &angle, const double length) {
    _x = cos(angle.value()) * length;
    _y = sin(angle.value()) * length;
}

double Vector2D::x() const {
    return _x;
}

double Vector2D::y() const {
    return _y;
}

double Vector2D::dot(const Vector2D &other) const {
    return (_x * other._x + _y * other._y);
}

double Vector2D::dist(const Vector2D &other) const {
    return (*this - other).length();
}

Vector2D Vector2D::scale(double scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

Vector2D Vector2D::normalize() const {
    if(this->length() == 0.0) return Vector2D(0.0, 0.0);

    double d = 1.0 / length();
    return Vector2D(_x * d, _y * d);
}

double Vector2D::length() const {
    return sqrt(_x * _x + _y * _y);
}

double Vector2D::angle() const {
    return this->toAngle().value();
}

Types::Angle Vector2D::toAngle() const {
    return Types::Angle(atan2(_y, _x));
}

Vector2D Vector2D::lerp(const Vector2D &other, double factor) const {
    return (this->scale(factor) + other.scale(1 - factor));
}

Vector2D Vector2D::rotate(double radians) const {
    double c = cos(radians);
    double s = sin(radians);

    return Vector2D(_x * c - _y * s, _x * s + _y * c);
}

Vector2D Vector2D::rotateAroundPoint(double radians, const Vector2D &pivot) const {
    double c = cos(radians);
    double s = sin(radians);

    // Calculate new position
    double rotatedX = (_x - pivot._x) * c - (_y - pivot._y) * s + pivot._x;
    double rotatedY = (_x - pivot._y) * s + (_y - pivot._y) * c + pivot._y;

    return Vector2D(rotatedX, rotatedY);
}

Vector2D Vector2D::project(const Vector2D &other) const {
    return other.scale(this->dot(other) / other.dot(other));
}

Vector2D Vector2D::project(const Vector2D &line_a, const Vector2D &line_b) const {
    Vector2D ab = line_b - line_a;
    Vector2D ap = (*this) - line_a;

    double t = ap.dot(ab) / ab.dot(ab);
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
    return (_x == _x) && (_y == _y);
}

double Vector2D::cross(const Vector2D &other) const {
    return (_x * other._y - _y * other._x);
}

Vector2D Vector2D::stretchToLength(double targetLength) const {
    if(length() == 0.0) {
        return Vector2D(targetLength, 0.0);
    }

    double frac = targetLength / length();
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

Vector2D Vector2D::operator+=(const double &scalar) {
    return Vector2D(_x += scalar, _y += scalar);
}

Vector2D Vector2D::operator-=(const Vector2D &other) {
    return Vector2D(_x -= other._x, _y -= other._y);
}

Vector2D Vector2D::operator-=(const double &scalar) {
    return Vector2D(_x -= scalar, _y -= scalar);
}

Vector2D Vector2D::operator*=(const Vector2D &other) {
    return Vector2D(_x *= other._x, _y *= other._y);
}

Vector2D Vector2D::operator*=(const double &scalar) {
    return Vector2D(_x *= scalar, _y *= scalar);
}

Vector2D Vector2D::operator/=(const Vector2D &other) {
    assert(!(other == Vector2D()) && "Division by zero");
    return Vector2D(_x /= other._x, _y /= other._y);
}

Vector2D Vector2D::operator/=(const double &scalar) {
    return Vector2D(_x /= scalar, _y /= scalar);
}

Vector2D Vector2D::operator+(const Vector2D &other) const {
    return Vector2D(_x + other._x, _y + other._y);
}

Vector2D Vector2D::operator+(const double &scalar) const {
    return Vector2D(_x + scalar, _y + scalar);
}

Vector2D Vector2D::operator-(const Vector2D &other) const {
    return Vector2D(_x - other._x, _y - other._y);
}

Vector2D Vector2D::operator-(const double &scalar) const {
    return Vector2D(_x - scalar, _y - scalar);
}

Vector2D Vector2D::operator*(const Vector2D &other) const {
    return Vector2D(_x * other._x, _y * other._y);
}

Vector2D Vector2D::operator*(const double &scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

Vector2D Vector2D::operator/(const Vector2D &other) const {
    return Vector2D(_x / other._x, _y / other._y);
}

Vector2D Vector2D::operator/(const double &scalar) const {
    return Vector2D(_x / scalar, _y / scalar);
}

}
