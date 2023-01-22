#include <Armorial/Geometry/LineSegment/LineSegment.h>
#include <Armorial/Geometry/Line/Line.h>

#include <Armorial/Utils/Utils.h>

#include <algorithm>
#include <math.h>
#include <spdlog/spdlog.h>

using namespace Geometry;

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

float LineSegment::length() const {
    return (end() - start()).length();
}

bool LineSegment::isPoint() const {
    return (start() == end());
}

float LineSegment::distanceToPoint(const Vector2D &point) const {
    if (isOnLine(project(point))) {
        return (project(point) - point).length();
    }
    if (relativePosition(project(point)).value() > 1.0f) {
        return (end() - point).length();
    }
    return (start() - point).length();
}

bool LineSegment::isOnLine(const Vector2D &point) const {
    if(isPoint()) {
        return (start() == point);
    }

    if(relativePosition(point).has_value()) {
        float relativePos = relativePosition(point).value();
        return (Utils::Compare::isEqual(relativePos, std::clamp(relativePos, 0.0f, 1.0f)));
    }

    return false;
}

Vector2D LineSegment::project(const Vector2D &point) const {
    if(isPoint()) {
        return start();
    }

    Vector2D projection = Line(*this).project(point);
    float t = relativePosition(projection).value();
    if(t < 0.0) {
        return start();
    }
    else if(t > 1.0) {
        return end();
    }

    return projection;
}

std::optional<Vector2D> LineSegment::intersects(const LineSegment &other) const {
    auto intersect_result = Line::intersect(start(), end(), other.start(), other.end());
    if(intersect_result.has_value()) {
        // Intersected point is contained at both the LineSegments that are previously expanded to infinite Lines
        if(this->isOnLine(intersect_result.value()) && other.isOnLine(intersect_result.value())) {
            return { intersect_result.value() };
        }
        // Intersected point is not contained at both the LineSegments
        else {
            return std::nullopt;
        }
    } else {
        // Check the case when one or both the LineSegment are points
        if(this->isPoint()) {
            if(other.isOnLine(start())) return { start() };
            else                        return std::nullopt;
        }
        else if(other.isPoint()) {
            if(this->isOnLine(other.start())) return { other.start() };
            else                              return std::nullopt;
        }

        // Check if both LineSegments are on the same infinite line
        Line inf_line = Line(*this);
        if(!inf_line.isOnLine(other.start())) {
            return std::nullopt; // LineSegments are not in the same infinite line
        }
        // Check if the LineSegments touch each other
        if ((distanceToPoint(other.start()) > 0.0f) && (distanceToPoint(other.end()) > 0.0f)) {
            return std::nullopt; // LineSegments do not touch each other
        }
        spdlog::warn("Segments are on the same infinite line and have multiple intersection points. Check if segment limits are correct");
        return Vector2D(1e10, 1e10);
    }
}

bool LineSegment::doesIntersect(const LineSegment &other) const {
    return intersects(other).has_value();
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

std::optional<float> LineSegment::relativePosition(const Vector2D &pointOnLine) const {
    Geometry::Line relatedLine(*this);
    if ((!relatedLine.isOnLine(pointOnLine)) || (isPoint())) {
        return std::nullopt;
    }
    float xDiff = this->end().x() - this->start().x();
    if (Utils::Compare::isEqual(xDiff, 0.0f)) {
        return (pointOnLine.y() - this->start().y()) / (this->end().y() - this->start().y());
    } else {
        return (pointOnLine.x() - this->start().x()) / xDiff;
    }
}
