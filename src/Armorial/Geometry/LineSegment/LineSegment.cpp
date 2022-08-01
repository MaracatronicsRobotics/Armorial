#include <Armorial/Geometry/LineSegment/LineSegment.h>
#include <Armorial/Geometry/Line/Line.h>

#include <Armorial/Utils/Utils.h>

#include <algorithm>
#include <math.h>

namespace Geometry {

LineSegment::LineSegment(const Vector2D &start, const Vector2D &end) {
    _start = start;
    _end = end;
}

Vector2D LineSegment::start() const {
    return _start;
}

Vector2D LineSegment::end() const {
    return _end;
}

double LineSegment::length() const {
    return (end() - start()).length();
}

bool LineSegment::isPoint() const {
    return (start() == end());
}

double LineSegment::distanceToPoint(const Vector2D &point) const {
    return (project(point) - point).length();
}

bool LineSegment::isOnLine(const Vector2D &point) const {
    if(isPoint()) {
        return (start() == point || end() == point);
    }

    if(Line(*this).isOnLine(point)) {
        double t = Line::relativePosition(start(), end(), point);
        return (Utils::Compare::isEqual(t, std::clamp(t, 0.0, 1.0)));
    }

    return false;
}

Vector2D LineSegment::project(const Vector2D &point) const {
    if(isPoint()) {
        return start();
    }

    Vector2D projection = Line(*this).project(point);
    double t = Line::relativePosition(start(), end(), projection);
    if(t < 0.0) {
        return start();
    }
    else if(t > 1.0) {
        return end();
    }

    return projection;
}

std::vector<Vector2D> LineSegment::intersects(const LineSegment &other) const {
    auto intersect_result = Line::intersect(start(), end(), other.start(), other.end());
    if(intersect_result.has_value()) {
        // Intersected point is contained at both the LineSegments that are previously expanded to infinite Lines
        if(this->isOnLine(intersect_result.value()) && other.isOnLine(intersect_result.value())) {
            return { intersect_result.value() };
        }
        // Intersected point is not contained at both the LineSegments
        else {
            return { };
        }
    }
    else {
        // Check the case when one or both the LineSegment are points
        if(this->isPoint()) {
            if(other.isOnLine(start())) return { start() };
            else                        return { };
        }
        else if(other.isPoint()) {
            if(this->isOnLine(other.start())) return { other.start() };
            else                              return { };
        }

        // Check if both LineSegments are on the same infinite line
        Line inf_line = Line(*this);
        if(!inf_line.isOnLine(other.start())) {
            return { };
        }

        std::vector<Vector2D> intersections;
        if(other.isOnLine(start())) {
            intersections.push_back(start());
        }
        if(other.isOnLine(end())) {
            intersections.push_back(end());
        }
        if(this->isOnLine(other.start())) {
            intersections.push_back(other.start());
        }
        if(this->isOnLine(other.end())) {
            intersections.push_back(other.end());
        }

        std::sort(intersections.begin(), intersections.end());
        intersections.erase(std::unique(intersections.begin(), intersections.end()), intersections.end());
        return intersections;
    }
}

bool LineSegment::doesIntersect(const LineSegment &other) const {
    return !intersects(other).empty();
}

Vector2D LineSegment::direction() const {
    return (end() - start());
}

void LineSegment::move(const Vector2D &amount) {
    _start += amount;
    _end += amount;
}

void LineSegment::rotate(const Geometry::Angle angle, const Vector2D pivot) {
    Vector2D midpoint = pivot;

    Vector2D startNewMidpoint = Vector2D(start().x() - midpoint.x(), start().y() - midpoint.y());
    Vector2D endNewMidpoint = Vector2D(end().x() - midpoint.x(), end().y() - midpoint.y());

    Vector2D startRotated = Vector2D((cos(angle.value()) * startNewMidpoint.x() - sin(angle.value()) * startNewMidpoint.y()), (sin(angle.value()) * startNewMidpoint.x() + cos(angle.value()) * startNewMidpoint.y()));
    Vector2D endRotated = Vector2D((cos(angle.value()) * endNewMidpoint.x() - sin(angle.value()) * endNewMidpoint.y()), (sin(angle.value()) * endNewMidpoint.x() + cos(angle.value()) * endNewMidpoint.y()));

    startRotated += midpoint;
    endRotated += midpoint;

    _start = startRotated;
    _end = endRotated;
}

}
