#include <Armorial/Geometry/Line/Line.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>

#include <spdlog/spdlog.h>
#include <math.h>

namespace Geometry {

Line::Line(Vector2D &p1, Vector2D &p2) {
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

double Line::distanceToLine(const Vector2D &point) const {
    return (project(point) - point).length();
}

Vector2D Line::project(const Vector2D &point) const {
    Vector2D ab = _p2 - _p1;
    Vector2D ap = point - _p1;

    return _p1 + ab * (ap.dot(ab) / pow(ab.length(), 2));
}

std::optional<Vector2D> Line::intersect(const Line &other) const {
    auto intersect_result = intersect(_p1, _p2, other._p1, other._p2);
    if(intersect_result.has_value()) {
        return intersect_result;
    }
    else if(other.isOnLine(_p1)) {
        return project(Vector2D(0, 0));
    }
    else {
        return std::nullopt;
    }
}

std::optional<Vector2D> Line::intersect(const Vector2D p1, const Vector2D p2, const Vector2D q1, const Vector2D q2) {
    Vector2D line_a = p1 - p2;
    Vector2D line_b = q1 - q2;

    double denominator = line_a.cross(line_b);
    if(fabs(denominator) >= 1e-4) {
        Vector2D l_aux = p1 - q1;
        double numerator = l_aux.cross(line_a);
        double u = numerator / denominator;
        return q1 - line_b * u;
    }

    return std::nullopt;
}

bool Line::isOnLine(const Vector2D &point) const {
    Vector2D ab = _p2 - _p1;
    Vector2D ap = point - _p1;

    return (fabs(ab.cross(ap)) < 1e-4);
}

double Line::relativePosition(const Vector2D &p1, const Vector2D &p2, const Vector2D &pointOnLine) {
    double xDiff = p2.x() - p1.x();
    if (xDiff == 0.0) {
        return (pointOnLine.y() - p1.y()) / (p2.y() - p1.y());
    }
    else {
        return (pointOnLine.x() - p1.x()) / xDiff;
    }
}

}
