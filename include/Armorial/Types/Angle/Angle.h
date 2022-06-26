#ifndef ARMORIAL_TYPES_ANGLE_H
#define ARMORIAL_TYPES_ANGLE_H

namespace Types {
    /*!
     * \brief The Types::Angle class is a class that stores angles on the interval [-π, π) and allows
     * operations with angles.
     */
    class Angle
    {
    public:
        /*!
         * \brief The Direction enum contains the possible directions which we can use
         * to rotate our angle to achieve some target angle value.
         */
        enum Direction {
            CLOCKWISE,
            COUNTER_CLOCKWISE
        };

        /*!
         * \brief Constructor of the Angle class, receiving a double value that represents the angle
         * value and normalize it.
         * \param angle The given double value of the angle. As it is normalized after you can give it
         * outside the range [-π, π).
         */
        Angle(double angle = 0.0);

        /*!
         * \brief Compute the shortest direction to achieve the target angle from the actual angle.
         * \param target The target angle.
         * \return The direction which we should take to achieve the target angle.
         * \note The angle difference can be calculated using the shortestAngleDiff method.
         */
        [[nodiscard]] Direction rotateDirection(const Angle& target) const;

        /*!
         * \brief Compute the shortest and absolute angle difference between the actual angle value and
         * the target Angle value.
         * \param target The target angle.
         * \return A value that contains the shortest angle diff in the range [0, π].
         * \note Use this combined with rotateDirection to discover the rotate direction.
         */
        [[nodiscard]] double shortestAngleDiff(const Angle& target) const;

        /*!
         * \brief Check if two Angle instances have the same angle values.
         * \param other The other Angle instance.
         * \return True if the Angle instances have the same angle values and False otherwise.
         */
        bool operator==(const Angle &other) const;

        /*!
         * \brief Check if two Angle instances have different angle values.
         * \param other The other Angle instance.
         * \return True if the Angle instances have different angle values and False otherwise.
         */
        bool operator!=(const Angle &other) const;

        /*!
         * \brief Compute the addition operator between this Angle and other Angle instance.
         * \param other The other Angle instance.
         * \return A new Angle instance that contains the result of the addition operation.
         * \note The resulted angle value will be normalized.
         */
        Angle operator+(const Angle &other) const;

        /*!
         * \brief Compute the subtraction operator between this Angle and other Angle instance.
         * \param other The other Angle instance.
         * \return A new Angle instance that contains the result of the subtraction operation.
         * \note The resulted angle value will be normalized.
         */
        Angle operator-(const Angle &other) const;

        /*!
         * \brief Compute the addition equal operator between this Angle and other Angle instance.
         * \param other The other Angle instance.
         * \return A new Angle instance that contains the result of the addition equal operation.
         * \note The resulted angle value will be normalized.
         */
        Angle &operator+=(const Angle &other);

        /*!
         * \brief Compute the subtration equal operator between this Angle and other Angle instance.
         * \param other The other Angle instance.
         * \return A new Angle instance that contains the result of the subtration equal operation.
         * \note The resulted angle value will be normalized.
         */
        Angle &operator-=(const Angle &other);

        /*!
         * \brief Set the angle value using a scalar value.
         * \param scalar A double value that contains the angle value that will be set.
         * \return A new angle instance that contains the set angle value.
         * \note The set angle will be normalized.
         */
        Angle &operator=(double scalar);

        /*!
         * \brief Get the actual value of angle for this Angle instance.
         * \return A double containing the value of the angle.
         */
        double value() const;

    private:
        // Angle value
        double _angle;

        /*!
         * \brief Compute the angle normalization to the range [-π, π).
         * \return A Angle instance that contains the normalized angle in the range.
         */
        Angle normalize();
    };
}

#endif // ARMORIAL_TYPES_ANGLE_H
