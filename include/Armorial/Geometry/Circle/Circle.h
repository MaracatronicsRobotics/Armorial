#ifndef ARMORIAL_GEOMETRY_CIRCLE_H
#define ARMORIAL_GEOMETRY_CIRCLE_H

#include <Armorial/Geometry/Line/Line.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>

#include <vector>

namespace Geometry {
    class Circle
    {
    public:
        /*!
         * \brief Construct a Circle instance with center at (0, 0) and radius 1.0
         */
        Circle();

        /*!
         * \brief Construct a Circle instance with given center and radius.
         * \param center The given center.
         * \param radius The given radius.
         */
        Circle(const Vector2D &center, const float &radius);

        /*!
         * \brief Default copy constructor
         */
        Circle(const Circle& other) = default;

        /*!
         * \brief Get the center of this Circle instance.
         * \return A Vector2D instance containing the center coordinates of this Circle instance.
         */
        [[nodiscard]] Vector2D center() const;

        /*!
         * \brief Get the radius of this Circle instance.
         * \return A float value containing the radius of this Circle.
         */
        [[nodiscard]] float radius() const;

        /*!
         * \brief Compute the intersection of the Circle instance with the Line instance.
         * \param line_segment The Line which the intersection will be computed.
         * \return A vector of points where this Circle intersects with the Line or
         * an empty vector of points if this Circle does not intersect with the Line.
         */
        [[nodiscard]] std::vector<Vector2D> intersects(const LineSegment& line_segment) const;

        /*!
         * \brief Check if this Circle contains a given point.
         * \param point The given point.
         * \return True if this Circle contains the given point and False otherwise.
         */
        [[nodiscard]] bool contains(const Vector2D& other) const;

        /*!
         * \brief Check if this Circle intersect a given line segment.
         * \param lineSegment The given line segment.
         * \return True if this Circle intersects a given line segment and False otherwise.
         */
        [[nodiscard]] bool doesIntersect(const LineSegment& other) const;

        /*!
         * \brief Compute the projection of a given point onto this Circle instance.
         * \param point The given point.
         * \return A point contained in the Circle that refers to the projection of the given point.
         */
        [[nodiscard]] Vector2D project(const Vector2D &point) const;

        /*!
         * \brief Move this Circle center coordinates by a given amount.
         * \param amount The given amount.
         */
        void move(const Vector2D& amount);

        /*!
         * \brief Check if two given Circle instances are equal comparing their center coordinates and radius.
         * \param other The other Circle instance.
         * \return True if the Circle instance are equal or False otherwise.
         */
        bool operator==(const Circle& other) const;

        /*!
         * \brief Check if two given Circle instances are different comparing their center coordinates and radius.
         * \param other The other Circle instance.
         * \return True if the Circle instance are different or False otherwise.
         */
        bool operator!=(const Circle& other) const;

        /*!
         * \brief Compute a move operation of this Circle instance by moving its center coordinates by a given Vector2D instance.
         * \param other The given Vector2D instance.
         * \return A Circle instance that contains the result of the operation.
         */
        Circle operator+(const Vector2D& other) const;
        Circle operator-(const Vector2D& other) const;
        Circle operator+=(const Vector2D& other);
        Circle operator-=(const Vector2D& other);

        /*!
         * \brief Compute a scale operation of this Circle instance by scaling the radius by a given float value.
         * \param scale The given float value.
         * \return A Circle instance that contains the result of the operation.
         */
        Circle operator*(const float &scale) const;
        Circle operator/(const float &scale) const;
        Circle operator*=(const float &scale);
        Circle operator/=(const float &scale);

    private:
        Vector2D _center;
        float _radius;
    };
}

#endif // CIRCLE_H
