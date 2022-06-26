#ifndef ARMORIAL_GEOMETRY_RECTANGLE_H
#define ARMORIAL_GEOMETRY_RECTANGLE_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>

namespace Geometry {
    /*!
     * \brief The Geometry::Rectangle class provides a representation for a rectangle object.
     */
    class Rectangle
    {
    public:
        /*!
         * \brief Constructs a instance of Rectangle by given corner points.
         * \param topLeft The top left corner position.
         * \param bottomRight The bottom right corner position.
         */
        Rectangle(const Vector2D& topLeft, const Vector2D& bottomRight);

        /*!
         * \brief Computes if this Rectangle instance contains a given point.
         * \param point The given point.
         * \return True if this Rectangle instance contains a given point and False otherwise.
         */
        [[nodiscard]] bool contains(const Vector2D& point) const;

        /*!
         * \brief Computes if this Rectangle instance contains a given point in a given margin error.
         * \param point The given point.
         * \param margin The given margin for error.
         * \return True if this Rectangle instance contains a given point in the margin error and False otherwise.
         */
        [[nodiscard]] bool contains(const Vector2D& point, double margin) const;

        /*!
         * \return Returns this Rectangle instance width.
         */
        [[nodiscard]] double width() const;

        /*!
         * \return Returns this Rectangle instance height.
         */
        [[nodiscard]] double height() const;

        /*!
         * \return Returns a Vector2D instance containing the center of this Rectangle.
         */
        [[nodiscard]] Vector2D center() const;

        /*!
         * \return Returns a Vector2D instance containing the top left corner of this Rectangle.
         */
        [[nodiscard]] Vector2D topLeft() const;

        /*!
         * \return Returns a Vector2D instance containing the top right corner of this Rectangle.
         */
        [[nodiscard]] Vector2D topRight() const;

        /*!
         * \return Returns a Vector2D instance containing the bottom left corner of this Rectangle.
         */
        [[nodiscard]] Vector2D bottomLeft() const;

        /*!
         * \return Returns a Vector2D instance containing the bottom right corner of this Rectangle.
         */
        [[nodiscard]] Vector2D bottomRight() const;

        /*!
         * \return Returns a LineSegment instance for the top line (formed by top corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment topLine() const;

        /*!
         * \return Returns a LineSegment instance for the right line (formed by right corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment rightLine() const;

        /*!
         * \return Returns a LineSegment instance for the bottom line (formed by bottom corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment bottomLine() const;

        /*!
         * \return Returns a LineSegment instance for the left line (formed by left corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment leftLine() const;

    private:
        Vector2D _topLeft;
        Vector2D _topRight;
        Vector2D _bottomLeft;
        Vector2D _bottomRight;
    };
}

#endif // ARMORIAL_GEOMETRY_RECTANGLE_H
