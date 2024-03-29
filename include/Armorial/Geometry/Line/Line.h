#ifndef LINE_H
#define LINE_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>

#include <optional>

#include <QString>

namespace Geometry {
    class LineSegment;
    /*!
     * \brief The Geometry::Line class provides a interface for a line with infinite length for both directions defined by two points.
     */
    class Line
    {
    public:
        /*!
         * \brief Creates a Line instance using two different Vector2D instances to define it.
         * \param p1 One of the points that will define the Line.
         * \param p2 The other point that will define the Line.
         */
        Line(const Vector2D &p1, const Vector2D &p2);

        /*!
         * \brief Creates a Line instance by expanding the LineSegment start and end coordinates.
         * \param other The LineSegment instance.
         */
        Line(const LineSegment &other);

        /*!
         * \brief Computes the Euclidean Distance from the point param coordinates to this Line instance.
         * \param point Point which will be used to calculate the distance.
         * \return A float value containing the distance from the point to this Line instance.
         */
        [[nodiscard]] float distanceToLine(const Vector2D &point) const;

        /*!
         * \brief Computes the projection of the given point onto this Line.
         * \param point Point which will be used to calculate the projection.
         * \return A Vector2D instance containing the projected point on this Line instance.
         */
        [[nodiscard]] Vector2D project(const Vector2D &point) const;

        /*!
         * \brief Compute a single intersection point between two Line instances.
         * \param other The other Line.
         * \return A std::optional object which stores a Vector2D instance containing (or not) the intersection point.
         * \note - In the case that the Lines does not intersect (parallelism), a std::nullopt will be returned. <br>
         *       - In the case that is a single intersection point, the Vector2D instance containing it will be returned. <br
         *       - In the case the lines are the same, a std::nullopt will be returned. Use == to verify similarity.
         */
        [[nodiscard]] std::optional<Vector2D> intersect(const Line &other) const;

        /*!
         * \brief Compute and determine if a point belongs to this Line instance.
         * \param point The point that will be used to determine if it belongs to this Line.
         * \return True if the given point lies on this Line and False otherwise.
         */
        [[nodiscard]] bool isOnLine(const Vector2D &point) const;

        /*!
         * \brief Check if two Line instances represent the same line.
         * \param other The other Line instance.
         * \return True if the Line instances represent the same line and False otherwise.
         */
        bool operator==(const Line &other) const;

        /*!
         * \brief toString method that returns a QString object.
         * \return The two Points of reference of Line.
         */
        QString toQString();

        /*!
         * \brief toString method that returns a std string object.
         * \return The two Points of reference of Line.
         */
        std::string toStdString();

    private:
        Vector2D _p1; // One of the points located on the Line
        Vector2D _p2; // Another of the points located on the Line, _p2 != _p1
    };
}

#endif // LINE_H
