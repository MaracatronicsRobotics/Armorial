#ifndef ARMORIAL_GEOMETRY_ARC_H
#define ARMORIAL_GEOMETRY_ARC_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/Circle/Circle.h>
#include <Armorial/Geometry/Line/Line.h>
#include <Armorial/Geometry/Angle/Angle.h>

#include <math.h>

namespace Geometry {
    /*!
     * \brief Defines the maximum angle value which a Arc should contain.
     */
    constexpr float ARC_MAX = 2.0 * M_PI - std::numeric_limits<float>::epsilon();

    /*!
     * \brief The Geometry::Arc class provides a interface which defines a arc which may be a circle / ellipse.
     */
    class Arc
    {
    public:
        /*!
         * \brief Default Geometry::Arc constructor, which initialize a unitary circle.
         */
        Arc();

        /*!
         * \brief Geometry::Arc constructor that creates a circle with the given parameters.
         * \param center The given center of the arc.
         * \param radius The given radius of the arc.
         */
        Arc(const Vector2D &center, const float &radius);

        /*!
         * \brief Geometry::Arc constructor that creates an arc that is part of a circle.
         * \param center The given center of the arc.
         * \param radius The given radius of the arc.
         * \param startAngle The start angle of the arc.
         * \param endAngle The end angle of the arc.
         */
        Arc(const Vector2D &center, const float &radius, const Geometry::Angle &startAngle, const Geometry::Angle &endAngle);

        /*!
         * \return The center of this Arc instance.
         */
        [[nodiscard]] Vector2D center() const;

        /*!
         * \return The radius of this Arc instance.
         */
        [[nodiscard]] float radius() const;

        /*!
         * \return The start angle of this Arc instance.
         */
        [[nodiscard]] Geometry::Angle startAngle() const;

        /*!
         * \return The end angle of this Arc instance.
         */
        [[nodiscard]] Geometry::Angle endAngle() const;

        /*!
         * \brief Checks if this arc defines a circle.
         * \return True if this arc defines a circle and False otherwise.
         */
        [[nodiscard]] bool isCircle() const;

        /*!
         * \brief Checks if a given angle is within the range that this Arc is defined.
         * \param angle The given angle.
         * \return True if the given angle is within the range that this Arc is defined and False otherwise.
         */
        [[nodiscard]] bool angleWithinArc(const Geometry::Angle &angle) const;

        /*!
         * \brief Checks if a given point is contained in this Arc.
         * \param point The given point.
         * \return True if the point is contained in this Arc and False otherwise.
         */
        [[nodiscard]] bool pointInArc(const Vector2D &point) const;

        /*!
         * \brief Compute the points at which a given LineSegment intersects this Arc instance, if these points exists.
         * \param lineSegment The given LineSegment instance.
         * \return A std::vector object containing the Vector2D points which defines the intersection points.
         */
        std::vector<Vector2D> intersectionWithLine(const LineSegment &lineSegment) const;

    private:
        Vector2D _center;         // Defines the center of the Arc
        float _radius;            // Defines the radius of the Arc
        Geometry::Angle _startAngle; // Defines the start angle of the Arc
        Geometry::Angle _endAngle;   // Defines the end angle of the Arc
        bool _reversed;           // Defines if the Arc methods will work with the angle limits switched or not
    };
}

#endif // ARMORIAL_GEOMETRY_ARC_H
