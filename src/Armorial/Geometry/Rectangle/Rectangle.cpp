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

float Rectangle::width() const {
    return std::abs(topRight().x() - topLeft().x());
}

float Rectangle::height() const {
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
    return LineSegment(_topLeft, _bottomLeft);
}

LineSegment Rectangle::bottomLine() const {
    return LineSegment(_bottomLeft, _bottomRight);
}

LineSegment Rectangle::rightLine() const {
    return LineSegment(_topRight, _bottomRight);
}

std::vector<LineSegment> Rectangle::boundary() const {
    return {leftLine(), topLine(), rightLine(), bottomLine()};
}

bool Rectangle::operator==(const Rectangle &other) const {
    return (this->_topLeft == other._topLeft) && (this->_bottomRight == other._bottomRight);
}

QString Rectangle::toQString() {
    QString rectangleStr = "";
    rectangleStr.append(QString("Top Left: (%1, %2)\n").arg(_topLeft.x()).arg(_topLeft.y()));
    rectangleStr.append(QString("Top Right: (%1, %2)\n").arg(_topRight.x()).arg(_topRight.y()));
    rectangleStr.append(QString("Bottom Left: (%1, %2)\n").arg(_bottomLeft.x()).arg(_bottomLeft.y()));
    rectangleStr.append(QString("Bottom Right: (%1, %2)").arg(_bottomRight.x()).arg(_bottomRight.y()));
    return rectangleStr;
}

std::string Rectangle::toStdString() {
    return toQString().toStdString();
}
