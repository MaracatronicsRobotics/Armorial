#ifndef ARMORIAL_COMMON_TYPES_OBJECT_H
#define ARMORIAL_COMMON_TYPES_OBJECT_H

#include <QReadWriteLock>

#include <Armorial/Common/Types/Types.h>

#include <Armorial/Geometry/Angle/Angle.h>
#include <Armorial/Geometry/Vector2D/Vector2D.h>

namespace Common {
namespace Types {
/*!
 * \brief The Types::Object class provides a base interface for any object in
 * the field.
 */
class Object {
public:
  /*!
   * \brief Default constructor for Types::Object class.
   */
  Object() = default;

  /*!
   * \brief Copy constructor.
   */
  Object(const Object &another);

  /*!
   * \brief Constructor for the Types::Object class.
   * \param position, velocity, acceleration, orientation, angularSpeed The
   * object data.
   */
  Object(const Geometry::Vector2D &position, const Geometry::Vector2D &velocity,
         const Geometry::Vector2D &acceleration,
         const Geometry::Angle &orientation = Geometry::Angle(),
         const float &angularSpeed = 0.0f);

  /*!
   * \brief Compute the distance from this object position to another.
   * \param position The position to compute distance.
   */
  float distTo(const Geometry::Vector2D &position);

  /*!
   * \brief Getters for the object attributes.
   */
  Geometry::Vector2D getPosition() const;
  Geometry::Vector2D getVelocity() const;
  Geometry::Vector2D getAcceleration() const;
  Geometry::Angle getOrientation() const;
  float getAngularSpeed() const;

  /*!
   * \brief Override for the = operator.
   */
  Object &operator=(const Object &another);

protected:
  /*!
   * \brief Setters for the object attributes.
   */
  void setPosition(const Geometry::Vector2D &position);
  void setVelocity(const Geometry::Vector2D &velocity);
  void setAcceleration(const Geometry::Vector2D &acceleration);
  void setOrientation(const Geometry::Angle &orientation);
  void setAngularSpeed(const float &angularSpeed);

private:
  // Object attributes
  Geometry::Vector2D _position;
  Geometry::Vector2D _velocity;
  Geometry::Vector2D _acceleration;
  Geometry::Angle _orientation;
  float _angularSpeed;

  // Mutex for data management
  mutable QReadWriteLock _mutex;
};
} // namespace Types
} // namespace Common

#endif // ARMORIAL_COMMON_TYPES_OBJECT_H
