#ifndef ARMORIAL_GEOMETRY_LINESEGMENT_H
#define ARMORIAL_GEOMETRY_LINESEGMENT_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>

#include <optional>

namespace Geometry {
    /*!
     * \brief The Geometry::LineSegment class provides a interface for a line segment object that starts at a given point and ends at a given point.
     */
    class LineSegment
    {
    public:
        /*!
         * \brief Creates a LineSegment instance with both start and end coordinates located at (0, 0).
         */
        LineSegment() = default;

        /*!
         * \brief Creates a LineSegment instance with given start and end coordinates.
         * \param start The given start coordinate.
         * \param end The given end coordinate.
         */
        LineSegment(const Vector2D &start, const Vector2D &end);

        /*!
         * \brief Default LineSegment copy constructor.
         */
        LineSegment(const LineSegment& other) = default;

        /*!
         * \return The start position of this LineSegment instance.
         */
        [[nodiscard]] Vector2D start() const;

        /*!
         * \return The end position of this LineSegment instance.
         */
        [[nodiscard]] Vector2D end() const;

        /*!
         * \brief Computes the length of this LineSegment instance.
         * \return A double value containing the length of this LineSegment instance.
         */
        [[nodiscard]] double length() const;

        /*!
         * \brief Check if this LineSegment instance is a point, i.e. it start and end points are the same.
         * \return True if this LineSegment is a point or False otherwise.
         */
        [[nodiscard]] bool isPoint() const;

        /*!
         * \brief Computes the distance from this LineSegment instance to a given point.
         * \param point The given point.
         * \return A double value containing the distance from this LineSegment instance to a given point.
         */
        [[nodiscard]] double distanceToPoint(const Vector2D &point) const;

        /*!
         * \brief Check if a given point is contained on this LineSegment instance.
         * \param point The given point.
         * \return True if point is contained or False otherwise.
         */
        [[nodiscard]] bool isOnLine(const Vector2D &point) const;

        /*!
         * \brief Computes the projection of a given point onto this LineSegment instance.
         * \param point The given point.
         * \return A Vector2D instance that contains the projected point onto this LineSegment instance.
         */
        [[nodiscard]] Vector2D project(const Vector2D &point) const;

        /*!
         * \brief Compute the intersection between to LineSegment instances.
         * \param other The other LineSegment instance.
         * \return A std::optional object which stores a Vector2D instance containing (or not) the intersection point.
         * \note - In the case that the LineSegment objects does not intersect, a std::nullopt will be returned. <br>
         *       - In the case that is a single intersection point, the Vector2D instance containing it will be returned. <br>
         *       - In the case that are multiple or even infinite intersections then the preference of the return will be: <br>
         *              - _start <br>
         *              - _end <br>
         *              - other _start
         */
        [[nodiscard]] std::optional<Vector2D> intersects(const LineSegment &other) const;

        /*!
         * \brief Check if two LineSegment instances intersect.
         * \param other The other LineSegment instance.
         * \return True if the LineSegment intersect each other or False otherwise.
         */
        [[nodiscard]] bool doesIntersect(const LineSegment &other) const;

        /*!
         * \brief Computes the direction vector.
         * \return A Vector2D instance that represents the direction in which this LineSegment instance points.
         */
        [[nodiscard]] Vector2D direction() const;

        /*!
         * \brief Move the line start and end points by a given Vector2D instance.
         * \param amount The given Vector2D instance.
         */
        void move(const Vector2D &amount);

        /*!
         * \brief Computes the rotation of this LineSegment instance around the pivot by a given angle.
         * \param angle The given angle.
         * \param pivot The given pivot position.
         */
        void rotate(const Types::Angle angle, const Vector2D pivot);

    private:
        Vector2D _start;
        Vector2D _end;
    };
}

#endif // ARMORIAL_GEOMETRY_LINESEGMENT_H
