#include <Armorial/Geometry/Rectangle/Rectangle.h>

namespace Geometry {

Rectangle::Rectangle(const Vector2D& topLeft, const Vector2D& bottomRight) {
    _topLeft = topLeft;
    _bottomRight = bottomRight;
    _topRight = Vector2D(bottomRight.x(), topLeft.y());
    _bottomLeft = Vector2D(topLeft.x(), bottomRight.y());
}

bool Rectangle::contains(const Vector2D &point) const {
    return (point.x() > _topLeft.x() && point.x() < _topRight.x())
            && (point.y() > _topLeft.y() && point.y() < _bottomLeft.y());
}

bool Rectangle::contains(const Vector2D &point, double margin) const {
    return (point.x() > (_topLeft.x() + margin) && point.x() < (_topRight.x() + margin))
            && (point.y() > (_topLeft.y() + margin) && point.y() < (_bottomLeft.y() + margin));
}

double Rectangle::width() const {
    return std::abs(topRight().x() - topLeft().x());
}

double Rectangle::height() const {
    return std::abs(_topLeft.y() - _bottomLeft.y());
}

Vector2D Rectangle::topLeft() const {
    return _topLeft;
}

Vector2D Rectangle::topRight() const {
    return _topRight;
}

Vector2D Rectangle::bottomLeft() const {
    return _bottomLeft;
}

Vector2D Rectangle::bottomRight() const {
    return _bottomRight;
}

LineSegment Rectangle::topLine() const {
    return LineSegment(_topLeft, _topRight);
}

LineSegment Rectangle::leftLine() const {
    return LineSegment(_bottomLeft, _topLeft);
}

LineSegment Rectangle::bottomLine() const {
    return LineSegment(_bottomRight, _bottomLeft);
}

LineSegment Rectangle::rightLine() const {
    return LineSegment(_topRight, _bottomRight);
}

}
