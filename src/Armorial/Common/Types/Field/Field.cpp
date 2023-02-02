#include <Armorial/Common/Types/Field/Field.h>

using namespace Common::Types;

Field::Field(const Enums::Side playSide, const float centerRadius,
             const float fieldLength, const float fieldWidth,
             const float goalDepth, const float goalWidth,
             const float penaltyDepth, const float penaltyWidth,
             const float penaltyMarkDistanceFromGoal) {
    _playSide = playSide;
    _centerRadius = centerRadius;
    _fieldLength = fieldLength;
    _fieldWidth = fieldWidth;
    _goalDepth = goalDepth;
    _goalWidth = goalWidth;
    _penaltyDepth = penaltyDepth;
    _penaltyWidth = penaltyWidth;
    _penaltyMarkDistanceFromGoal = penaltyMarkDistanceFromGoal;
}

Geometry::Circle Field::centerCircle() const {
    return Geometry::Circle(Geometry::Vector2D(0, 0), _centerRadius);
}

Geometry::Rectangle Field::field() const {
    Geometry::Vector2D topLeftCorner(-length()/2.0f, width()/2.0f);
    Geometry::Vector2D bottomRightCorner(length()/2.0f, -width()/2.0f);
    return Geometry::Rectangle(topLeftCorner, bottomRightCorner);
}

Geometry::Rectangle Field::leftField() const {
    Geometry::Vector2D topLeftCorner = field().topLeft();
    Geometry::Vector2D midBottomCorner(0.0, -width()/2.0f);
    return Geometry::Rectangle(topLeftCorner, midBottomCorner);
}

Geometry::Rectangle Field::rightField() const {
    Geometry::Vector2D midTopCorner(0.0, width()/2.0f);
    Geometry::Vector2D bottomRightCorner = field().bottomRight();
    return Geometry::Rectangle(midTopCorner, bottomRightCorner);
}

Geometry::Rectangle Field::leftPenaltyArea() const {
    Geometry::Vector2D leftPenaltyTopLeftCorner(-length()/2.0f, penaltyWidth()/2.0f);
    Geometry::Vector2D leftPenaltyBottomRightCorner(-length()/2.0f + penaltyDepth(), -penaltyWidth()/2.0f);
    return Geometry::Rectangle(leftPenaltyTopLeftCorner, leftPenaltyBottomRightCorner);
}

Geometry::Rectangle Field::rightPenaltyArea() const {
    Geometry::Vector2D rightPenaltyTopLeftCorner(length()/2.0f - penaltyDepth(), penaltyWidth()/2.0f);
    Geometry::Vector2D rightPenaltyBottomRightCorner(length()/2.0f, -penaltyWidth()/2.0f);
    return Geometry::Rectangle(rightPenaltyTopLeftCorner, rightPenaltyBottomRightCorner);
}

bool Field::playingLeftSide() const {
    return (_playSide == Common::Enums::Side::SIDE_LEFT);
}

float Field::minX() const {
    return -length()/2.0f;
}

float Field::maxX() const {
    return length()/2.0f;
}

float Field::minY() const {
    return -width()/2.0f;
}

float Field::maxY() const {
    return width()/2.0f;
}

float Field::length() const {
    return _fieldLength;
}

float Field::width() const {
    return _fieldWidth;
}

float Field::goalDepth() const {
    return _goalDepth;
}

float Field::goalWidth() const {
    return _goalWidth;
}

float Field::penaltyDepth() const {
    return _penaltyDepth;
}

float Field::penaltyWidth() const {
    return _penaltyWidth;
}

float Field::penaltyMarkDistanceFromGoal() const {
    return _penaltyMarkDistanceFromGoal;
}

float Field::centerRadius() const {
    return _centerRadius;
}

Geometry::Vector2D Field::ourGoalCenter() const {
    if(playingLeftSide()) {
        Geometry::Vector2D leftPenaltyAreaCenter = leftPenaltyArea().center();
        return Geometry::Vector2D(leftPenaltyAreaCenter.x() - penaltyDepth()/2.0f, leftPenaltyAreaCenter.y());
    }
    else {
        Geometry::Vector2D rightPenaltyAreaCenter = rightPenaltyArea().center();
        return Geometry::Vector2D(rightPenaltyAreaCenter.x() + penaltyDepth()/2.0f, rightPenaltyAreaCenter.y());
    }
}

Geometry::Vector2D Field::ourGoalLeftPost() const {
    Geometry::Vector2D goalCenter = ourGoalCenter();
    float offset = (playingLeftSide() ? -goalWidth()/2.0f : goalWidth()/2.0f);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::ourGoalRightPost() const {
    Geometry::Vector2D goalCenter = ourGoalCenter();
    float offset = (playingLeftSide() ? goalWidth()/2.0f : -goalWidth()/2.0f);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::ourPenaltyMark() const {
    Geometry::Vector2D goalCenter = theirGoalCenter();
    float offset = (playingLeftSide() ? -penaltyMarkDistanceFromGoal() : penaltyMarkDistanceFromGoal());
    return Geometry::Vector2D(goalCenter.x() - offset, goalCenter.y());
}

Geometry::Rectangle Field::ourField() const {
    return (playingLeftSide() ? leftField() : rightField());
}

Geometry::Rectangle Field::ourPenaltyArea() const {
    return (playingLeftSide() ? leftPenaltyArea() : rightPenaltyArea());
}

Geometry::Vector2D Field::theirGoalCenter() const {
    // Take our goal center and just reflect the x coordinate
    Geometry::Vector2D ourCenter = ourGoalCenter();
    return Geometry::Vector2D(-ourCenter.x(), ourCenter.y());
}

Geometry::Vector2D Field::theirGoalLeftPost() const {
    Geometry::Vector2D goalCenter = theirGoalCenter();
    float offset = (playingLeftSide() ? goalWidth()/2.0f : -goalWidth()/2.0f);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::theirGoalRightPost() const {
    Geometry::Vector2D goalCenter = theirGoalCenter();
    float offset = (playingLeftSide() ? -goalWidth()/2.0f : goalWidth()/2.0f);
    return Geometry::Vector2D(goalCenter.x(), goalCenter.y() + offset);
}

Geometry::Vector2D Field::theirPenaltyMark() const {
    Geometry::Vector2D goalCenter = ourGoalCenter();
    float offset = (playingLeftSide() ? penaltyMarkDistanceFromGoal() : -penaltyMarkDistanceFromGoal());
    return Geometry::Vector2D(goalCenter.x() - offset, goalCenter.y());
}

Geometry::Rectangle Field::theirField() const {
    return (playingLeftSide() ? rightField() : leftField());
}

Geometry::Rectangle Field::theirPenaltyArea() const {
    return (playingLeftSide() ? rightPenaltyArea() : leftPenaltyArea());
}

Geometry::Rectangle Field::topRightQuadrant() const {
    return Geometry::Rectangle({0.0, width() / 2.0f}, {length() / 2.0f, 0.0});
}

Geometry::Rectangle Field::topLeftQuadrant() const {
    return Geometry::Rectangle({-(length() / 2.0f), width() / 2.0f}, {0.0, 0.0});
}

Geometry::Rectangle Field::bottomLeftQuadrant() const {
    return Geometry::Rectangle({-(length() / 2.0f), 0.0}, {0.0, -(width() / 2.0f)});
}

Geometry::Rectangle Field::bottomRightQuadrant() const {
    return Geometry::Rectangle({0.0, 0.0}, {length() / 2.0f, -(width() / 2.0f)});
}
