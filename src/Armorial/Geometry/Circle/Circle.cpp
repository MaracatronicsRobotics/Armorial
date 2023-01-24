#include <Armorial/Geometry/Circle/Circle.h>

#include <Armorial/Utils/Utils.h>

using namespace Geometry;

Circle::Circle(const Vector2D &center, const float &radius) {
    _center = center;
    _radius = radius;
}

Vector2D Circle::center() const {
    return _center;
}

float Circle::radius() const {
    return _radius;
}

std::vector<Vector2D> Circle::intersects(const LineSegment &line_segment) const {
    Vector2D direction_vector = line_segment.direction();
    Vector2D f = line_segment.start() - center();

    float a = direction_vector.dotProduct(direction_vector);
    float b = 2.0 * f.dotProduct(direction_vector);
    float c = f.dotProduct(f) - radius() * radius();

    std::optional<std::pair<float,float>> values = Utils::Algebra::solveQuadratic(a,b,c);

    // Compute intersections
    std::vector<Vector2D> intersections;

    if(values.has_value()){
        if(Utils::Compare::isEqual(values->first, std::clamp(values->first, 0.0f, 1.0f))) {
            intersections.push_back(line_segment.start() + direction_vector * values->first);
        }

        if(Utils::Compare::isEqual(values->second, std::clamp(values->second, 0.0f, 1.0f)) && !Utils::Compare::isEqual(values->second, values->first)) {
            intersections.push_back(line_segment.start()+ direction_vector * values->second);
        }
    }

    return intersections;
}

bool Circle::contains(const Vector2D &other) const {
    return (fabs((center() - other).length()) <= radius());
}

bool Circle::doesIntersect(const LineSegment &other) const {
    return (other.distanceToPoint(center()) <= radius());
}

Vector2D Circle::project(const Vector2D &point) const {
    return center() + (point - center()).stretchToLength(radius());
}

void Circle::move(const Vector2D &amount) {
    this->_center += amount;
}

bool Circle::operator==(const Circle &other) const {
    return (center() == other.center()) && (Utils::Compare::isEqual(radius(), other.radius()));
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

Circle Circle::operator*(const float &scale) const {
    return Circle(center(), radius() * fabs(scale));
}

Circle Circle::operator/(const float &scale) const {
    return Circle(center(), radius() / fabs(scale));
}

Circle Circle::operator*=(const float &scale) {
    return Circle(center(), _radius *= fabs(scale));
}

Circle Circle::operator/=(const float &scale) {
    return Circle(center(), _radius /= fabs(scale));
}
