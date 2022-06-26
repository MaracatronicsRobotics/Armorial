#include <Armorial/Types/Field/Field.h>

namespace Types {

Field::Field(const Side playSide, const float centerRadius,
             const float fieldLength, const float fieldWidth,
             const float goalDepth, const float goalWidth,
             const float penaltyDepth, const float penaltyWidth,
             const float penaltyMarkDistanceFromCenter) {
    _playSide = playSide;
    _centerRadius = centerRadius;
    _fieldLength = fieldLength;
    _fieldWidth = fieldWidth;
    _goalDepth = goalDepth;
    _goalWidth = goalWidth;
    _penaltyDepth = penaltyDepth;
    _penaltyWidth = penaltyWidth;
    _penaltyMarkDistanceFromCenter = penaltyMarkDistanceFromCenter;
}

Geometry::Circle Field::centerCircle() {
    return Geometry::Circle(Geometry::Vector2D(0, 0), _centerRadius);
}

Geometry::Rectangle Field::field() {
    Geometry::Vector2D topLeftCorner(-length()/2.0, width()/2.0);
    Geometry::Vector2D bottomRightCorner(length()/2.0, -width()/2.0);
    return Geometry::Rectangle(topLeftCorner, bottomRightCorner);
}

Geometry::Rectangle Field::leftField() {
    Geometry::Vector2D topLeftCorner = field().topLeft();
    Geometry::Vector2D midBottomCorner(0.0, -width()/2.0);
    return Geometry::Rectangle(topLeftCorner, midBottomCorner);
}

Geometry::Rectangle Field::rightField() {
    Geometry::Vector2D midTopCorner(0.0, width()/2.0);
    Geometry::Vector2D bottomRightCorner = field().bottomRight();
    return Geometry::Rectangle(midTopCorner, bottomRightCorner);
}

Geometry::Rectangle Field::leftPenaltyArea() {
    Geometry::Vector2D leftPenaltyTopLeftCorner(-length()/2.0, goalWidth()/2.0);
    Geometry::Vector2D leftPenaltyBottomRightCorner(-length()/2.0 + penaltyDepth(), -goalWidth()/2.0);
    return Geometry::Rectangle(leftPenaltyTopLeftCorner, leftPenaltyBottomRightCorner);
}

Geometry::Rectangle Field::rightPenaltyArea() {
    Geometry::Vector2D rightPenaltyTopLeftCorner(length()/2.0 - penaltyDepth(), goalWidth()/2.0);
    Geometry::Vector2D rightPenaltyBottomRightCorner(length()/2.0, -goalWidth()/2.0);
    return Geometry::Rectangle(rightPenaltyTopLeftCorner, rightPenaltyBottomRightCorner);
}

bool Field::playingLeftSide() {
    return (_playSide == SIDE_LEFT);
}

float Field::minX() {
    return -length()/2.0;
}

float Field::maxX() {
    return length()/2.0;
}

float Field::minY() {
    return -width()/2.0;
}

float Field::maxY() {
    return width()/2.0;
}

float Field::length() {
    return _fieldLength;
}

float Field::width() {
    return _fieldWidth;
}

float Field::goalDepth() {
    return _goalDepth;
}

float Field::goalWidth() {
    return _goalWidth;
}

float Field::penaltyDepth() {
    return _penaltyDepth;
}

float Field::penaltyWidth() {
    return _penaltyWidth;
}

float Field::penaltyMarkDistanceFromCenter() {
    return _penaltyMarkDistanceFromCenter;
}

float Field::centerRadius() {
    return _centerRadius;
}

Geometry::Vector2D Field::ourGoalCenter() {
    if(playingLeftSide()) {
        Geometry::Vector2D leftPenaltyAreaCenter = leftPenaltyArea().center();
        return Geometry::Vector2D(leftPenaltyAreaCenter.x() - penaltyDepth()/2.0, leftPenaltyAreaCenter.y());
    }
    else {
        Geometry::Vector2D rightPenaltyAreaCenter = rightPenaltyArea().center();
        return Geometry::Vector2D(rightPenaltyAreaCenter.x() + penaltyDepth()/2.0, rightPenaltyAreaCenter.y());
    }
}

Geometry::Vector2D Field::ourGoalLeftPost() {
    Geometry::Vector2D goalCenter = ourGoalCenter();
    float offset = (playingLeftSide() ? -goalWidth()/2.0 : goalWidth()/2.0);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::ourGoalRightPost() {
    Geometry::Vector2D goalCenter = ourGoalCenter();
    float offset = (playingLeftSide() ? goalWidth()/2.0 : -goalWidth()/2.0);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::ourPenaltyMark() {
    Geometry::Vector2D fieldCenter = field().center();
    float offset = (playingLeftSide() ? -penaltyMarkDistanceFromCenter() : penaltyMarkDistanceFromCenter());
    return Geometry::Vector2D(fieldCenter.x() - offset, fieldCenter.y());
}

Geometry::Rectangle Field::ourField() {
    return (playingLeftSide() ? leftField() : rightField());
}

Geometry::Rectangle Field::ourPenaltyArea() {
    return (playingLeftSide() ? leftPenaltyArea() : rightPenaltyArea());
}

Geometry::Vector2D Field::theirGoalCenter() {
    // Take our goal center and just reflect the x coordinate
    Geometry::Vector2D ourCenter = ourGoalCenter();
    return Geometry::Vector2D(-ourCenter.x(), ourCenter.y());
}

Geometry::Vector2D Field::theirGoalLeftPost() {
    Geometry::Vector2D goalCenter = theirGoalCenter();
    float offset = (playingLeftSide() ? goalWidth()/2.0 : -goalWidth()/2.0);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::theirGoalRightPost() {
    Geometry::Vector2D goalCenter = theirGoalCenter();
    float offset = (playingLeftSide() ? -goalWidth()/2.0 : goalWidth()/2.0);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::theirPenaltyMark() {
    Geometry::Vector2D fieldCenter = field().center();
    float offset = (playingLeftSide() ? penaltyMarkDistanceFromCenter() : -penaltyMarkDistanceFromCenter());
    return Geometry::Vector2D(fieldCenter.x() - offset, fieldCenter.y());
}

Geometry::Rectangle Field::theirField() {
    return (playingLeftSide() ? rightField() : leftField());
}

Geometry::Rectangle Field::theirPenaltyArea() {
    return (playingLeftSide() ? rightPenaltyArea() : leftPenaltyArea());
}

}
