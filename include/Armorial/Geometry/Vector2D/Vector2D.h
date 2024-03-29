﻿#ifndef ARMORIAL_GEOMETRY_VECTOR2D_H
#define ARMORIAL_GEOMETRY_VECTOR2D_H

#include <Armorial/Geometry/Angle/Angle.h>

#include <QString>

namespace Geometry {
    /*!
     * \brief The Geometry::Vector2D class stores a vector of two floats that starts from (0, 0) to (_x, _y).
     */
    class Vector2D
    {
    public:
        /*!
         * \brief The default constructor for Vector2D, which initialize _x and _y as 0.
         */
        Vector2D() = default;

        /*!
         * \brief Vector2D constructor that receive parameters.
         * \param x The x value.
         * \param y The y value.
         */
        Vector2D(const float &x, const float &y);

        /*!
         * \brief Vector2D constructor that receive a Geometry::Angle and length as parameter.
         * \param angle The Geometry::Angle object which the angle value will be extracted.
         * \param length The length of the Vector2D started from (0, 0) coordinates.
         */
        Vector2D(const Geometry::Angle &angle, const float &length);

        /*!
         * \brief Default copy constructor.
         * \param other The Vector2D which will be copied.
         */
        Vector2D(const Vector2D& other) = default;

        /*!
         * \brief Default copy assignment operator.
         * \param other The Vector2D which will be copied.
         */
        Vector2D &operator=(const Vector2D &other) = default;

        /*!
         * \brief Get the _x coordinate value.
         * \return A float value containing the _x coordinate.
         */
        float x() const;

        /*!
         * \brief Get the _y coordinate value.
         * \return A float value containing the _y coordinate.
         */
        float y() const;

        /*!
         * \brief Caculate the dot product of this Vector2D instance and another.
         * \param other The other Vector2D instance.
         * \return The dot product between the two Vector2D instances.
         */
        [[nodiscard]] float dotProduct(const Vector2D &other) const;

        /*!
         * \brief Compute the distance from this Vector2D instance to another.
         * \param other The another Vector2D instance.
         * \return The distance from this Vector2D instance to another.
         */
        float dist(const Vector2D &other) const;

        /*!
         * \brief Scale this Vector2D instance by a scalar.
         * \param scalar The scalar value which will be used to compute the scale.
         * \return A Vector2D instance that contains a copy of this Vector2D instance scaled.
         */
        Vector2D scale(const float &scalar) const;

        /*!
         * \brief Compute the normalization of this Vector2D instance to a length of 1.
         * \return A Vector2D instance that contains a copy of this Vector2D instance normalized.
         * \note This operation preserves the angle.
         */
        Vector2D normalize() const;

        /*!
         * \brief Computes the length of this Vector2D instance.
         * \return The length of this Vector2D instance.
         */
        float length() const;

        /*!
         * \brief Computes the length2 of this Vector2D instance.
         * \return The length2 of this Vector2D instance.
         */
        float length2() const;

        /*!
         * \brief Computes the angle of this Vector2D instance viewed from the center of the field (0.0, 0.0). <br>
         * As this uses the atan2 function, the following behavior is expected: <br>
         *      - The positive x-axis has angle value 0; <br>
         *      - Vectors with a positive _y value will have a negative angle value; <br>
         *      - Vectors with a negative or zero _y value will have a positive angle value; <br>
         *      - The angle of the zero vector is undefined.
         * \return The angle value of this Vector2D instance viewed from the center of the field (0.0, 0.0).
         */
        float angle() const;

        /*!
         * \brief Get the Geometry::Angle object using the angle() result from this Vector2D instance.
         * \return A Geometry::Angle object that contains the angle() result from this Vector2D instance.
         */
        Geometry::Angle toAngle() const;

        /*!
         * \brief Performs a linear interpolation/extrapolation of this Vector2D instance by a factor. <br>
         *      - If factor == 0, the result will be this Vector2D instance. <br>
         *      - If factor == 1, the result is a copy of the other Vector2D instance. <br>
         *      - For any other factor, the result will be given by (factor*100)% along the way between this vector and the other.
         * \param other The other Vector2D instance.
         * \param factor The factor which will be used to calculate the interpolation/extrapolation between the Vector2D instances.
         * \return A Vector2D that contains the result from the operation.
         */
        Vector2D lerp(const Vector2D &other, const float &factor) const;

        /*!
         * \brief Computate the rotation of this Vector2D instance around the origin.
         * \param radians The amount of the rotation given in radians.
         * \return A Vector2D instance that contains the result from the operation.
         */
        Vector2D rotate(const float &radians) const;

        /*!
         * \brief Computate the rotation of this Vector2D instance around a given pivot.
         * \param radians The amount of the rotation given in radians.
         * \param pivot A Vector2D instance that will be used as pivot for the rotation.
         * \return A Vector2D instance that contains the result from the operation.
         */
        Vector2D rotateAroundPoint(const float &radians, const Vector2D &pivot) const;

        /*!
         * \brief Computes the projection of this Vector2D instance onto another Vector2D instance.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance that contains the result from the operation.
         */
        Vector2D project(const Vector2D &other) const;

        /*!
         * \brief Computes the projection of this Vector2D instance onto a line segment that is defined by
         * two another Vector2D instances defined by (line_a, line_b).
         * \param line_a The first definition of the line segment.
         * \param line_b The final definition of the line segment.
         * \return A Vector2D instance which points are contained at the segment defined by (line_a, line_b)
         * and is the closest Vector2D from this instance.
         */
        Vector2D project(const Vector2D &line_a, const Vector2D &line_b) const;

        /*!
         * \brief Check if the components of this Vector2D instance are valid.
         * \return True if the components are valid or False otherwise.
         */
        bool isValid() const;

        /*!
         * \brief Calculate the cross product with this Vector2D instance with another.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance that contains the result for the operation.
         */
        float crossProductMagnitude(const Vector2D &other) const;

        /*!
         * \brief Creates a Vector2D instance with the same angle as this but with the given
         * length.
         * \param length The given length which this Vector2D instance will be strectched to.
         * \return A Vector2D instance with the stretched length.
         */
        Vector2D stretchToLength(const float &targetLength) const;

        /*!
         * \brief Check if two Vector2D instances have the same coordinates.
         * \param other The other Vector2D instance.
         * \return True if the Vector2D instances have the same coordinates and False otherwise.
         */
        bool operator==(const Vector2D &other) const;

        /*!
         * \brief Check if two Vector2D instances have different coordinates.
         * \param other The other Vector2D instance.
         * \return True if the Vector2D instances have different coordinates and False otherwise.
         */
        bool operator!=(const Vector2D &other) const;

        /*!
         * \brief Compare the length of two Vector2D instances.
         * \param other The other Vector2D instance.
         * \return True if this Vector2D instance has a lower length than other.
         */
        bool operator<(const Vector2D &other) const;

        /*!
         * \brief Sum other Vector2D instance coordinates onto this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which coordinates has the sum result.
         */
        Vector2D operator+=(const Vector2D &other);

        /*!
         * \brief Subtract other Vector2D instance coordinates onto this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which coordinates has the subtract result.
         */
        Vector2D operator-=(const Vector2D &other);

        /*!
         * \brief Multiply other Vector2D instance coordinates onto this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which coordinates has the multiply result.
         */
        Vector2D operator*=(const Vector2D &other);

        /*!
         * \brief Divide other Vector2D instance coordinates onto this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which coordinates has the divide result.
         */
        Vector2D operator/=(const Vector2D &other);

        /*!
         * \brief Sum a scalar to Vector2D components.
         * \param other A float scalar value.
         * \return A Vector2D instance which coordinates has the sum result.
         */
        Vector2D operator+=(const float &scalar);

        /*!
         * \brief Subtract a scalar to Vector2D components.
         * \param other A float scalar value.
         * \return A Vector2D instance which coordinates has the subtract result.
         */
        Vector2D operator-=(const float &scalar);

        /*!
         * \brief Multiply a scalar to Vector2D components.
         * \param other A float scalar value.
         * \return A Vector2D instance which coordinates has the multiplication result.
         */
        Vector2D operator*=(const float &scalar);

        /*!
         * \brief Divide a scalar to Vector2D components.
         * \param other A float scalar value.
         * \return A Vector2D instance which coordinates has the division result.
         */
        Vector2D operator/=(const float &scalar);

        /*!
         * \brief Add another Vector2D instance component-wise to this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which contains the result of the sum.
         */
        Vector2D operator+(const Vector2D &other) const;

        /*!
         * \brief Add a scalar component-wise to this instance.
         * \param other The float scalar value.
         * \return A Vector2D instance which contains the result of the sum.
         */
        Vector2D operator+(const float &scalar) const;

        /*!
         * \brief Subtract another Vector2D instance component-wise to this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which contains the result of the subtraction.
         */
        Vector2D operator-(const Vector2D &other) const;

        /*!
         * \brief Subtract a scalar component-wise to this instance.
         * \param other The float scalar value.
         * \return A Vector2D instance which contains the result of the subtraction.
         */
        Vector2D operator-(const float &scalar) const;

        /*!
         * \brief Multiply another Vector2D instance component-wise to this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which contains the result of the multiplication.
         */
        Vector2D operator*(const Vector2D &other) const;

        /*!
         * \brief Multiply a scalar component-wise to this instance.
         * \param other The float scalar value.
         * \return A Vector2D instance which contains the result of the multiplication.
         */
        Vector2D operator*(const float &scalar) const;

        /*!
         * \brief Divide another Vector2D instance component-wise to this.
         * \param other The other Vector2D instance.
         * \return A Vector2D instance which contains the result of the division.
         */
        Vector2D operator/(const Vector2D &other) const;

        /*!
         * \brief Divide a scalar component-wise to this instance.
         * \param other The float scalar value.
         * \return A Vector2D instance which contains the result of the division.
         */
        Vector2D operator/(const float &scalar) const;

        /*!
         * \brief toString method that returns a QString object.
         * \return The Vector2D x and y values.
         */
        QString toQString();

        /*!
         * \brief toString method that returns a std string object.
         * \return The Vector2D x and y values.
         */
        std::string toStdString();

    private:
        float _x;
        float _y;
    };
}

#endif // ARMORIAL_GEOMETRY_VECTOR2D_H
