#ifndef ARMORIAL_GEOMETRY_TRIANGLE_H
#define ARMORIAL_GEOMETRY_TRIANGLE_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>

namespace Geometry {
    /*!
     * \brief The Geometry::Triangle class provides a interface that descbribe a triangle in the field.
     */
    class Triangle
    {
    public:
        Triangle() = default;

        /*!
         * \brief Constructs a Triangle instance with the provided corner points.
         * \param p1 The first given corner point.
         * \param p2 The second given corner point.
         * \param p3 The third given corner point.
         */
        Triangle(const Vector2D &p1, const Vector2D &p2, const Vector2D &p3);

        /*!
         * \return The corners of this Triangle instance.
         */
        [[nodiscard]] std::vector<Vector2D> corners() const;

        /*!
         * \brief Computes if this Triangle contains a given point.
         * \param point The given point.
         * \return True if this Triangle contains the given point and False otherwise.
         */
        [[nodiscard]] bool contains(const Vector2D &point) const;

        /*!
         * \brief Computes this Triangle area.
         * \return A float containing the computed value of the area.
         */
        [[nodiscard]] float area() const;

        /*!
         * \brief Get the boundary lines of this Triangle.
         * \return A list containing the line segments that compunds the boundary of the Triangle.
         */
        [[nodiscard]] std::vector<LineSegment> boundary() const;

        /*!
         * \brief Check if this Triangle intersect a given line segment.
         * \param lineSegment The given line segment.
         * \return True if this Triangle intersect a given line segment and False otherwise.
         */
        [[nodiscard]] bool doesIntersect(const LineSegment& lineSegment) const;

        /*!
         * \brief Computes the intersection between this Triangle and a given line segment.
         * \param lineSegment The given line segment.
         * \return A list containing the intersection points with this Triangle and the given line segment.
         */
        [[nodiscard]] std::vector<Vector2D> intersect(const LineSegment& lineSegment) const;

        /*!
         * \brief toString method that returns a QString object.
         * \return The Vertices Points.
         */
        QString toQString();

        /*!
         * \brief toString method that returns a std string object.
         * \return The Vertices Points.
         */
        std::string toStdString();

    private:
        Vector2D _p1;
        Vector2D _p2;
        Vector2D _p3;
    };
}

#endif // ARMORIAL_GEOMETRY_TRIANGLE_H
