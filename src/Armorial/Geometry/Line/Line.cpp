#include <Armorial/Geometry/Line/Line.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>
#include <Armorial/Utils/Utils.h>

#include <spdlog/spdlog.h>
#include <math.h>

using namespace Geometry;

Line::Line(const Vector2D &p1, const Vector2D &p2) {
    _p1 = p1;
    _p2 = p2;
    if(p1 == p2) {
        spdlog::warn("Created a Line with p1 == p2 == ({}, {}) which generated a undefined line.", p1.x(), p1.y());
    }
}

Line::Line(const LineSegment &other) {
    _p1 = other.start();
    _p2 = other.end();
    if(_p1 == _p2) {
        spdlog::warn("Created a Line from a LineSegment with p1 == p2 == ({}, {}) which generated a undefined line.", _p1.x(), _p1.y());
    }
}

float Line::distanceToLine(const Vector2D &point) const {
    return (project(point) - point).length();
}

Vector2D Line::project(const Vector2D &point) const {
    Vector2D ab = _p2 - _p1;
    Vector2D ap = point - _p1;

    return _p1 + ab * (ap.dotProduct(ab) / pow(ab.length(), 2));
}

std::optional<Vector2D> Line::intersect(const Line &other) const {
    Vector2D line_a = _p1 - _p2;
    Vector2D line_b = other._p1 - other._p2;

    float denominator = line_a.x() * line_b.y() - line_a.y() * line_b.x();
    if(fabs(denominator) >= 1e-4) {
        Vector2D l_aux = _p1 - other._p1;
        float numerator = l_aux.x() * line_a.y() - l_aux.y() * line_a.x();
        float u = numerator / denominator;
        return other._p1 - line_b * u;
    }

    return std::nullopt;
}

bool Line::isOnLine(const Vector2D &point) const {
    if (_p2 == _p1) {
        return (point == _p1);
    }
    Vector2D ab = _p2 - _p1;
    Vector2D ap = point - _p1;

    return (ab.crossProductMagnitude(ap) < 1e-4);
}

bool Line::operator==(const Line &other) const {
    return ((project(other._p1) == other._p1) && (project(other._p2) == other._p2));
}

QString Line::toQString() {
    return QString("P1: (%1, %2)\nP2: (%3, %4)").arg(_p1.x()).arg(_p1.y()).arg(_p2.x()).arg(_p2.y());
}

std::string Line::toStdString() {
    return toQString().toStdString();
}
