#include <Armorial/Geometry/Rectangle/Rectangle.h>

#include <math.h>

using namespace Geometry;

Rectangle::Rectangle(const Vector2D& topLeft, const Vector2D& bottomRight) {
    updateCorners(topLeft, bottomRight);
}

void Rectangle::updateCorners(const Vector2D &topLeft, const Vector2D &bottomRight) {
    _topLeft = topLeft;
    _bottomRight = bottomRight;
    _topRight = Vector2D(bottomRight.x(), topLeft.y());
    _bottomLeft = Vector2D(topLeft.x(), bottomRight.y());
}

double Rectangle::width() const {
    return std::abs(topRight().x() - topLeft().x());
}

double Rectangle::height() const {
    return std::abs(_topLeft.y() - _bottomLeft.y());
}

Vector2D Rectangle::center() const {
    return Vector2D((topLeft().x() + bottomRight().x()) / 2, (topLeft().y() + bottomRight().y()) / 2);
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

std::vector<LineSegment> Rectangle::boundary() const {
    return {leftLine(), topLine(), rightLine(), bottomLine()};
}
