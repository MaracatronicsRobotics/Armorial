#include <Armorial/Geometry/Circle/Circle.h>
#include <Armorial/Utils/Utils.h>

namespace Geometry {

Circle::Circle(const Vector2D &center, const double radius) {
    _center = center;
    _radius = radius;
}

Vector2D Circle::center() const {
    return _center;
}

double Circle::radius() const {
    return _radius;
}

std::vector<Vector2D> Circle::intersects(const LineSegment &line_segment) const {
    Vector2D direction_vector = line_segment.direction();
    Vector2D f = line_segment.start() - center();

    double a = direction_vector.dot(direction_vector);
    double b = 2.0 * f.dot(direction_vector);
    double c = f.dot(f) - radius() * radius();

    std::optional<std::pair<double,double>> values = Utils::Algebra::solveQuadratic(a,b,c);

    // Compute intersections
    std::vector<Vector2D> intersections;

    if(values.has_value()){
        if(values->first == std::clamp(values->first, 0.0, 1.0)) {
            intersections.push_back(line_segment.start() + direction_vector * values->first);
        }

        if(values->second == std::clamp(values->second, 0.0, 1.0) && values->second != values->first) {
            intersections.push_back(line_segment.start()+ direction_vector * values->second);
        }
    }

    return intersections;
}

bool Circle::doesIntersectOrContain(const Vector2D &other) const {
    return (fabs((center() - other).length()) <= radius());
}

bool Circle::doesIntersectOrContain(const Line &other) const {
    return (other.distanceToLine(center()) <= radius());
}

Vector2D Circle::project(const Vector2D &point) const {
    return center() + (point - center()).stretchToLength(radius());
}

bool Circle::operator==(const Circle &other) const {
    return (center() == other.center()) && (radius() == other.radius());
}

bool Circle::operator!=(const Circle &other) const {
    return !(*this == other);
}

Circle Circle::operator+(const Vector2D &other) const {
    return Circle(center() + other, radius());
}

Circle Circle::operator-(const Vector2D &other) const {
    return Circle(center() - other, radius());
}

Circle Circle::operator+=(const Vector2D &other) {
    return Circle(_center += other, radius());
}

Circle Circle::operator-=(const Vector2D &other) {
    return Circle(_center -= other, radius());
}

Circle Circle::operator*(double scale) const {
    return Circle(center(), radius() * fabs(scale));
}

Circle Circle::operator/(double scale) const {
    return Circle(center(), radius() / fabs(scale));
}

Circle Circle::operator*=(double scale) {
    return Circle(center(), _radius *= fabs(scale));
}

Circle Circle::operator/=(double scale) {
    return Circle(center(), _radius /= fabs(scale));
}

}
