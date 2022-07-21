#include <Armorial/Geometry/Arc/Arc.h>

namespace Geometry {

Arc::Arc() {
    _center = Vector2D();
    _radius = 1.0;
    _startAngle = 0.0;
    _endAngle = ARC_MAX;
}

Arc::Arc(const Vector2D &center, const float &radius) {
    _center = center;
    _radius = radius;
    _startAngle = 0.0;
    _endAngle = ARC_MAX;
}

Arc::Arc(const Vector2D &center, const float &radius, const Types::Angle &startAngle, const Types::Angle &endAngle) {
    _center = center;
    _radius = radius;
    _startAngle = startAngle;
    _endAngle = endAngle;
}

Vector2D Arc::center() const {
    return _center;
}

float Arc::radius() const {
    return _radius;
}

Types::Angle Arc::startAngle() const {
    return _startAngle;
}

Types::Angle Arc::endAngle() const {
    return _endAngle;
}

bool Arc::isCircle() const {
    return (startAngle() == 0.0f && endAngle() == ARC_MAX);
}

bool Arc::angleWithinArc(const Types::Angle &angle) const {
    return (angle.value() >= startAngle().value() && angle.value() <= endAngle().value());
}

bool Arc::pointInArc(const Vector2D &point) const {
    Vector2D normPoint = point - center();
    return (angleWithinArc(normPoint.angle()) && normPoint.length() <= radius());
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

}
