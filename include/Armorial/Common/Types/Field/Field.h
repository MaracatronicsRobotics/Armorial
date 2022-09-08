#ifndef ARMORIAL_COMMON_TYPES_FIELD_H
#define ARMORIAL_COMMON_TYPES_FIELD_H

#include <Armorial/Common/Types/Types.h>
#include <Armorial/Common/Enums/Side/Side.h>

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/Circle/Circle.h>
#include <Armorial/Geometry/Rectangle/Rectangle.h>

namespace Common {
namespace Types {
    /*!
     * \brief The Types::Field class provides a interface to setup and get field positions based on the
     * provided constraints.
     */
    class Field
    {
    public:
        /*!
         * \brief Field default constructor
         */
        Field() = default;

        /*!
         * \brief Constructs a Field instance.
         * \param playSide The Side enum that indicates which is the side our team plays.
         * \param centerRadius the field center radius constraint.
         * \param fieldLength The field length constraint.
         * \param fieldWidth The field width constraint.
         * \param goalDepth The goal depth constraint.
         * \param goalWidth The goal width constraint.
         * \param penaltyDepth The penalty depth constraint.
         * \param penaltyWidth The penalty width constraint.
         * \param penaltyMarkDistanceFromGoal The penalty mark distance from goal center.
         * \note All the given units should be the same.
         */
        Field(const Enums::Side playSide, const float centerRadius,
              const float fieldLength, const float fieldWidth,
              const float goalDepth, const float goalWidth,
              const float penaltyDepth, const float penaltyWidth,
              const float penaltyMarkDistanceFromGoal);

        /*!
         * \return A Geometry::Circle object centered at (0, 0) with radius _centerRadius.
         */
        Geometry::Circle centerCircle() const;

        /*!
         * \return A Geometry::Rectangle object that contains the shape of the field
         * defined by the constructor contraints.
         */
        Geometry::Rectangle field() const;

        /*!
         * \return A Geometry::Rectangle object related to the left half of the field.
         */
        Geometry::Rectangle leftField() const;

        /*!
         * \return A Geometry::Rectangle object related to the right half of the field.
         */
        Geometry::Rectangle rightField() const;

        /*!
         * \return A Geometry::Rectangle object related to the left penalty area.
         */
        Geometry::Rectangle leftPenaltyArea() const;

        /*!
         * \return A Geometry::Rectangle object related to the right penalty area.
         */
        Geometry::Rectangle rightPenaltyArea() const;

        /*!
         * \return True if we are playing at left side and False otherwise.
         */
        bool playingLeftSide() const;

        /*!
         * \return The minimum x-axis value of the field.
         */
        float minX() const;

        /*!
         * \return The maximum x-axis value of the field.
         */
        float maxX() const;

        /*!
         * \return The minimum y-axis value of the field.
         */
        float minY() const;

        /*!
         * \return The maximum y-axis value of the field.
         */
        float maxY() const;

        /*!
         * \return The length of the field.
         */
        float length() const;

        /*!
         * \return The width of the field.
         */
        float width() const;

        /*!
         * \return The goal depth.
         */
        float goalDepth() const;

        /*!
         * \return The goal width.
         */
        float goalWidth() const;

        /*!
         * \return The penalty depth.
         */
        float penaltyDepth() const;

        /*!
         * \return The penalty width.
         */
        float penaltyWidth() const;

        /*!
         * \return The penalty mark distance from goal center.
         */
        float penaltyMarkDistanceFromGoal() const;

        /*!
         * \return The center radius.
         */
        float centerRadius() const;

        /*!
         * \return The position of the center of our goal.
         */
        Geometry::Vector2D ourGoalCenter() const;

        /*!
         * \return The position of the right post of our goal.
         */
        Geometry::Vector2D ourGoalRightPost() const;

        /*!
         * \return The position of the left post of our goal.
         */
        Geometry::Vector2D ourGoalLeftPost() const;

        /*!
         * \return The position of our penalty mark.
         */
        Geometry::Vector2D ourPenaltyMark() const;

        /*!
         * \return A Geometry::Rectangle object related to our half of the field.
         */
        Geometry::Rectangle ourField() const;

        /*!
         * \return A Geometry::Rectangle object related to our penalty area.
         */
        Geometry::Rectangle ourPenaltyArea() const;

        /*!
         * \return The position of the center of their goal.
         */
        Geometry::Vector2D theirGoalCenter() const;

        /*!
         * \return The position of the right post of their goal.
         */
        Geometry::Vector2D theirGoalRightPost() const;

        /*!
         * \return The position of the left post of their goal.
         */
        Geometry::Vector2D theirGoalLeftPost() const;

        /*!
         * \return The position of their penalty mark.
         */
        Geometry::Vector2D theirPenaltyMark() const;

        /*!
         * \return A Geometry::Rectangle object related to their half of the field.
         */
        Geometry::Rectangle theirField() const;

        /*!
         * \return A Geometry::Rectangle object related to their penalty area.
         */
        Geometry::Rectangle theirPenaltyArea() const;

        /*!
         * \return A Geometry::Rectangle object that describes the top right quadrant area.
         */
        Geometry::Rectangle topRightQuadrant() const;

        /*!
         * \return A Geometry::Rectangle object that describes the top left quadrant area.
         */
        Geometry::Rectangle topLeftQuadrant() const;

        /*!
         * \return A Geometry::Rectangle object that describes the bottom left quadrant area.
         */
        Geometry::Rectangle bottomLeftQuadrant() const;

        /*!
         * \return A Geometry::Rectangle object that describes the bottom right quadrant area.
         */
        Geometry::Rectangle bottomRightQuadrant() const;


    private:
        Enums::Side _playSide;
        float _centerRadius;
        float _fieldLength;
        float _fieldWidth;
        float _goalDepth;
        float _goalWidth;
        float _penaltyDepth;
        float _penaltyWidth;
        float _penaltyMarkDistanceFromGoal;
    };
}
}

#endif // ARMORIAL_COMMON_TYPES_FIELD_H
