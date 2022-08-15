#ifndef ARMORIAL_COMMON_TYPES_OBJECT_H
#define ARMORIAL_COMMON_TYPES_OBJECT_H

#define INVALID_IDENTIFIER 255

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <Armorial/Geometry/Angle/Angle.h>

#include <QReadWriteLock>

namespace Common {
namespace Types {
    /*!
     * \brief The Common::Types::Object class provides a interface to generalize objects in the environment,
     * providing default parameters which objects in the field should have, such as position, orientation and
     * identifier.
     */
    class Object
    {
    public:
        Object(const Geometry::Vector2D &position, const Geometry::Angle &orientation = Geometry::Angle(), const quint8 identifier = INVALID_IDENTIFIER);

        /*!
         * \brief Set the position of this object instance to a given position.
         * \param position The given position.
         */
        void setPosition(const Geometry::Vector2D &position);

        /*!
         * \return This object instance position.
         */
        Geometry::Vector2D getPosition();

        /*!
         * \brief Set the velocity of this object instance to a given velocity.
         * \param velocity The given velocity.
         */
        void setVelocity(const Geometry::Vector2D &velocity);

        /*!
         * \return This object instance velocity.
         */
        Geometry::Vector2D getVelocity();

        /*!
         * \brief Set the acceleration of this object instance to a given acceleration.
         * \param acceleration The given acceleration.
         */
        void setAcceleration(const Geometry::Vector2D &acceleration);

        /*!
         * \return This object instance acceleration.
         */
        Geometry::Vector2D getAcceleration();

        /*!
         * \brief Set the orientation of this object instance to a given orientation.
         * \param orientation The given orientation.
         */
        void setOrientation(const Geometry::Angle &orientation);

        /*!
         * \return This object instance orientation.
         */
        Geometry::Angle getOrientation();

        /*!
         * \brief Set the identifier of this object instance to a given identifier.
         * \param identifier The given identifier.
         */
        void setIdentifier(const quint8 &identifier);

        /*!
         * \return This object instance identifier.
         */
        quint8 getIdentifier();

    private:
        // Object-related vars
        Geometry::Vector2D _position;
        Geometry::Vector2D _velocity;
        Geometry::Vector2D _acceleration;
        Geometry::Angle _orientation;
        quint8 _identifier;

        // Mutex for data modification / acquisition
        QReadWriteLock _dataMutex;
    };
}
}

#endif // ARMORIAL_COMMON_TYPES_OBJECT_H
