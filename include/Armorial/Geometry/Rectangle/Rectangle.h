#ifndef ARMORIAL_GEOMETRY_RECTANGLE_H
#define ARMORIAL_GEOMETRY_RECTANGLE_H

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/LineSegment/LineSegment.h>

#include <Armorial/Common/Types/Traits/Traits.h>

namespace Geometry {
    /*!
     * \brief The Geometry::Rectangle class provides a representation for a rectangle object.
     */
    class Rectangle
    {
    public:
        /*!
         * \brief Constructs a default instance for rectangle.
         * \note The corner points in this case are by default at {0.0, 0.0}, so remember to update them.
         */
        Rectangle() = default;

        /*!
         * \brief Constructs a instance of Rectangle by given corner points.
         * \param topLeft The top left corner position.
         * \param bottomRight The bottom right corner position.
         */
        Rectangle(const Vector2D& topLeft, const Vector2D& bottomRight);

        /*!
         * \tparam T The type of the point variable.
         * \brief Computes if this Rectangle instance contains a given point.
         * \param point The given point.
         * \return True if this Rectangle instance contains a given point and False otherwise.
         * \note This method will only work if the type T contains coordinates (.x() and .y() methods).
         */
        template<typename T>
        [[nodiscard]] std::enable_if_t<Common::Types::has_coordinates_v<T>, bool> contains(const T& point) const {
            return (point.x() >= _topLeft.x() && point.x() <= _topRight.x())
                    && (point.y() >= _bottomLeft.y() && point.y() <= _topLeft.y());
        }

        /*!
         * \tparam T The type of the point variable.
         * \brief Computes if this Rectangle instance contains a given point in a given margin error.
         * \param point The given point.
         * \param margin The given margin for error.
         * \return True if this Rectangle instance contains a given point in the margin error and False otherwise.
         * \note This method will only work if the type T contains coordinates (.x() and .y() methods).
         */
        template<typename T>
        [[nodiscard]] std::enable_if_t<Common::Types::has_coordinates_v<T>, bool> contains(const T& point, const float &margin) const {
            return (point.x() >= (_topLeft.x() - margin) && point.x() <= (_topRight.x() + margin))
                    && (point.y() >= (_bottomLeft.y() - margin) && point.y() <= (_topLeft.y() + margin));
        }

        /*!
         * \brief Update this Rectangle instance with the given corners.
         * \param topLeft, bottomRight The given corners.
         */
        void updateCorners(const Vector2D& topLeft, const Vector2D& bottomRight);

        /*!
         * \return Returns this Rectangle instance width.
         */
        [[nodiscard]] float width() const;

        /*!
         * \return Returns this Rectangle instance height.
         */
        [[nodiscard]] float height() const;

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
         * \return Returns a LineSegment instance for the top line (formed by top (left to right) corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment topLine() const;

        /*!
         * \return Returns a LineSegment instance for the right line (formed by right (top to bottom) corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment rightLine() const;

        /*!
         * \return Returns a LineSegment instance for the bottom line (formed by bottom (left to right) corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment bottomLine() const;

        /*!
         * \return Returns a LineSegment instance for the left line (formed by left (top to bottom) corners) of this Rectangle.
         */
        [[nodiscard]] LineSegment leftLine() const;

        /*!
         * \return Returns a list of LineSegment instances containig all the boundary line segments of this Rectangle.
         */
        std::vector<LineSegment> boundary() const;

        /*!
         * \brief Check if two Rectangles instances have the same corners.
         * \param other The other Rectangle instance.
         * \return True if the Rectangles instances have the same corners and False otherwise.
         */
        bool operator==(const Rectangle &other) const;

    private:
        Vector2D _topLeft;
        Vector2D _topRight;
        Vector2D _bottomLeft;
        Vector2D _bottomRight;
    };
}

#endif // ARMORIAL_GEOMETRY_RECTANGLE_H
