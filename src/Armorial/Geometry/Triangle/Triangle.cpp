#include <Armorial/Geometry/Triangle/Triangle.h>

#include <Armorial/Utils/Utils.h>

#include <algorithm>

using namespace Geometry;

Triangle::Triangle(const Vector2D &p1, const Vector2D &p2, const Vector2D &p3) {
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;
}

std::vector<Vector2D> Triangle::corners() const {
    return { _p1, _p2, _p3 };
}

bool Triangle::contains(const Vector2D &point) const {
    // https://www.baeldung.com/cs/check-if-point-is-in-2d-triangle (3.3)
    // Get this triangle instance area
    float triangleArea = this->area();

    // Compute the sum area using the given point as corner
    float sumArea = 0.0f;
    sumArea += Triangle(_p1, _p2, point).area();
    sumArea += Triangle(_p1, _p3, point).area();
    sumArea += Triangle(_p2, _p3, point).area();

    // Return if sumArea and triangleArea matches
    return Utils::Compare::isEqual(triangleArea, sumArea);
}

float Triangle::area() const {
    Vector2D AB = _p2 - _p1;
    Vector2D AC = _p3 - _p1;

    float cross_prod = AB.crossProductMagnitude(AC);
    return (cross_prod / 2.0f);
}

std::vector<LineSegment> Triangle::boundary() const {
    return { LineSegment(_p1, _p2), LineSegment(_p2, _p3), LineSegment(_p3, _p1) };
}

bool Triangle::doesIntersect(const LineSegment &lineSegment) const {
    std::vector<LineSegment> triangleBoundary = boundary();
    bool intersect = false;
    for(auto &ls : triangleBoundary) {
        intersect |= lineSegment.doesIntersect(ls);
    }

    return intersect;
}

std::vector<Vector2D> Triangle::intersect(const LineSegment &lineSegment) const {
    std::vector<Vector2D> intersections;
    std::vector<LineSegment> triangleBoundary = boundary();
    for (const auto &triangleLine : triangleBoundary) {
        std::optional<Vector2D> intersection = lineSegment.intersects(triangleLine);
        if (intersection.has_value()) {
            intersections.push_back(intersection.value());
        }
    }

    std::sort(intersections.begin(), intersections.end());
    intersections.erase(std::unique(intersections.begin(), intersections.end()), intersections.end());

    return intersections;
}
