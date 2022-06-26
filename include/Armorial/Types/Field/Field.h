#ifndef ARMORIAL_TYPES_FIELD_H
#define ARMORIAL_TYPES_FIELD_H

#include <Armorial/Types/Types.h>

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/Circle/Circle.h>
#include <Armorial/Geometry/Rectangle/Rectangle.h>

namespace Types {
    enum Side {
        SIDE_LEFT,
        SIDE_RIGHT
    };

    /*!
     * \brief The Types::Field class provides a interface to setup and get field positions based on the
     * provided constraints.
     */
    class Field
    {
    public:
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
         * \param penaltyMarkDistanceFromCenter The penalty mark distance from field center.
         * \note All the given units should be the same.
         */
        Field(const Side playSide, const float centerRadius,
              const float fieldLength, const float fieldWidth,
              const float goalDepth, const float goalWidth,
              const float penaltyDepth, const float penaltyWidth,
              const float penaltyMarkDistanceFromCenter);

        /*!
         * \return A Geometry::Circle object centered at (0, 0) with radius _centerRadius.
         */
        Geometry::Circle centerCircle();

        /*!
         * \return A Geometry::Rectangle object that contains the shape of the field
         * defined by the constructor contraints.
         */
        Geometry::Rectangle field();

        /*!
         * \return A Geometry::Rectangle object related to the left half of the field.
         */
        Geometry::Rectangle leftField();

        /*!
         * \return A Geometry::Rectangle object related to the right half of the field.
         */
        Geometry::Rectangle rightField();

        /*!
         * \return A Geometry::Rectangle object related to the left penalty area.
         */
        Geometry::Rectangle leftPenaltyArea();

        /*!
         * \return A Geometry::Rectangle object related to the right penalty area.
         */
        Geometry::Rectangle rightPenaltyArea();

        /*!
         * \return True if we are playing at left side and False otherwise.
         */
        bool playingLeftSide();

        /*!
         * \return The minimum x-axis value of the field.
         */
        float minX();

        /*!
         * \return The maximum x-axis value of the field.
         */
        float maxX();

        /*!
         * \return The minimum y-axis value of the field.
         */
        float minY();

        /*!
         * \return The maximum y-axis value of the field.
         */
        float maxY();

        /*!
         * \return The length of the field.
         */
        float length();

        /*!
         * \return The width of the field.
         */
        float width();

        /*!
         * \return The goal depth.
         */
        float goalDepth();

        /*!
         * \return The goal width.
         */
        float goalWidth();

        /*!
         * \return The penalty depth.
         */
        float penaltyDepth();

        /*!
         * \return The penalty width.
         */
        float penaltyWidth();

        /*!
         * \return The penalty mark distance from center.
         */
        float penaltyMarkDistanceFromCenter();

        /*!
         * \return The center radius.
         */
        float centerRadius();

        /*!
         * \return The position of the center of our goal.
         */
        Geometry::Vector2D ourGoalCenter();

        /*!
         * \return The position of the right post of our goal.
         */
        Geometry::Vector2D ourGoalRightPost();

        /*!
         * \return The position of the left post of our goal.
         */
        Geometry::Vector2D ourGoalLeftPost();

        /*!
         * \return The position of our penalty mark.
         */
        Geometry::Vector2D ourPenaltyMark();

        /*!
         * \return A Geometry::Rectangle object related to our half of the field.
         */
        Geometry::Rectangle ourField();

        /*!
         * \return A Geometry::Rectangle object related to our penalty area.
         */
        Geometry::Rectangle ourPenaltyArea();

        /*!
         * \return The position of the center of their goal.
         */
        Geometry::Vector2D theirGoalCenter();

        /*!
         * \return The position of the right post of their goal.
         */
        Geometry::Vector2D theirGoalRightPost();

        /*!
         * \return The position of the left post of their goal.
         */
        Geometry::Vector2D theirGoalLeftPost();

        /*!
         * \return The position of their penalty mark.
         */
        Geometry::Vector2D theirPenaltyMark();

        /*!
         * \return A Geometry::Rectangle object related to their half of the field.
         */
        Geometry::Rectangle theirField();

        /*!
         * \return A Geometry::Rectangle object related to their penalty area.
         */
        Geometry::Rectangle theirPenaltyArea();

    private:
        Side _playSide;
        float _centerRadius;
        float _fieldLength;
        float _fieldWidth;
        float _goalDepth;
        float _goalWidth;
        float _penaltyDepth;
        float _penaltyWidth;
        float _penaltyMarkDistanceFromCenter;
    };
}

#endif // ARMORIAL_TYPES_FIELD_H
