#include <Armorial/Geometry/Arc/Arc.h>
#include <spdlog/spdlog.h>

using namespace Geometry;

Arc::Arc() {
    _center = Vector2D();
    _radius = 1.0;
    _startAngle = Geometry::Angle(-Geometry::Angle::PI);
    _endAngle = Geometry::Angle(Geometry::Angle::PI);
    _reversed = false;
}

Arc::Arc(const Vector2D &center, const float &radius) {
    _center = center;
    _radius = radius;
    _startAngle = Geometry::Angle(-Geometry::Angle::PI);
    _endAngle = Geometry::Angle(Geometry::Angle::PI);
    _reversed = false;
}

Arc::Arc(const Vector2D &center, const float &radius, const Geometry::Angle &startAngle, const Geometry::Angle &endAngle) {
    _center = center;
    _radius = radius;
    if (startAngle.value() > endAngle.value()) {
        _endAngle = startAngle;
        _startAngle = endAngle;
        _reversed = true;
    } else {
        _startAngle = startAngle;
        _endAngle = endAngle;
        _reversed = false;
    }
}

Vector2D Arc::center() const {
    return _center;
}

float Arc::radius() const {
    return _radius;
}

Geometry::Angle Arc::startAngle() const {
    if (_reversed) {
        return _endAngle;
    } else {
        return _startAngle;
    }
}

Geometry::Angle Arc::endAngle() const {
    if (_reversed) {
        return _startAngle;
    } else {
        return _endAngle;
    }
}

bool Arc::isCircle() const {
    return (startAngle() == -Geometry::Angle::PI && endAngle() == Geometry::Angle::PI);
}

bool Arc::angleWithinArc(const Geometry::Angle &angle) const {
    if (_reversed) {
        // include start and final angle in calculations
        return !(angle.value() > _startAngle.value() && angle.value() < _endAngle.value());
    } else {
        return (angle.value() >= _startAngle.value() && angle.value() <= _endAngle.value());
    }
}

bool Arc::pointInArc(const Vector2D &point) const {
    Vector2D normPoint = point - center();
    return (angleWithinArc(normPoint.angle()) && (normPoint.length() <= radius()));
}

float Arc::arcAngle() const{
    float startAngle = (_startAngle.value() < 0) ? _startAngle.value() + M_PI*2 : _startAngle.value();
    float endAngle = (_endAngle.value() < 0) ? _endAngle.value() + M_PI*2 : _endAngle.value();
    return std::abs(startAngle - endAngle);
}
std::vector<Vector2D> Arc::intersectionWithLine(const LineSegment &lineSegment) const {
    std::vector<Vector2D> intersections;

    // Creates a full-circle based on the parameters
    const Circle arcAsCircle = Circle(_center, _radius);
    const std::vector<Vector2D> intersectionsWithCircle = arcAsCircle.intersects(lineSegment);

    // For each point in the intersection result, check if it is contained in the arc
    // and put it into the vector if True
    for(auto p : intersectionsWithCircle) {
        if(pointInArc(p)) {
            intersections.push_back(p);
        }
    }

    return intersections;
}

QString Arc::toQString() {
    QString arcStr = QString("Center: (%1, %2)\nRadius: %3\nStart: %4; End: %5\n%6")
                         .arg(_center.x())
                         .arg(_center.y())
                         .arg(_radius)
                         .arg(_startAngle.value())
                         .arg(_endAngle.value())
                         .arg(_reversed ? "Reversed" : "Not Reversed");
    return arcStr;
}

std::string Arc::toStdString() {
    return toQString().toStdString();
}
