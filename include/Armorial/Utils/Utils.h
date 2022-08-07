#ifndef ARMORIAL_UTILS_H
#define ARMORIAL_UTILS_H

#include <QNetworkDatagram>

#include <math.h>
#include <type_traits>

#include <Armorial/Common/Types/Traits/Traits.h>
#include <Armorial/Geometry/Rectangle/Rectangle.h>

namespace Utils {
    namespace Compare {
        /*!
         * \tparam T The type of the values that will be compared.
         * \brief Performs a floating point comparison using the '<=' operator.
         * \param v1, v2 The floating point values which will be compared.
         * \note The T type needs to be a floating type.
         */
        template <typename T>
        [[nodiscard]] inline static constexpr std::enable_if_t<std::is_floating_point_v<T>, bool> isEqual(const T& v1, const T& v2) {
            return fabs(v2 - v1) <= std::numeric_limits<T>::epsilon();
        }
    }

    namespace Proto {
        /*!
         * \tparam T The type of the protobuf object that the network datagram will be converted to
         * \brief Convert a QNetworkDatagram to the protobuf type T
         * \param datagram The reference for the QNetworkDatagram object
         * \param type The reference for the object of type T
         */
        template <typename T>
        [[nodiscard]] inline static constexpr bool convertDatagramToType(QNetworkDatagram &datagram, T& type) noexcept {
            return (type.ParseFromArray(datagram.data().data(), datagram.data().size()));
        }
    }

    namespace Angles {
        /*!
         * \tparam T The given type of the input.
         * \return The given value in radians converted to degrees.
         */
        template<typename T>
        inline static constexpr std::enable_if_t<std::is_floating_point_v<T>, T> radToDeg(const T& radians) {
            return (radians * (180.0 / M_PI));
        }

        /*!
         * \tparam T The given type of the input.
         * \return The given value in degrees converted to radians.
         */
        template<typename T>
        inline static constexpr std::enable_if_t<std::is_floating_point_v<T>, T> degToRad(const T& degrees) {
            return (degrees * (M_PI / 180.0));
        }

    }

    namespace Algebra {
        /*!
         * \brief Solves a quadratic equation that possesses the form ax² + bx + c = 0.
         * \param a, b, c The quadratic equation constraints.
         * \return A std::optinal containing two float values t0, t1.
         * \note t0 <= t1.
         * \note If the discriminant is == 0, the optinal will be returned empty (std::nullopt).
         */
        [[nodiscard]] inline std::optional<std::pair<float, float>> solveQuadratic(const float &a, const float &b, const float &c) {
            double discriminant = (b * b) - (4 * a * c);
            if(discriminant < 0.0) {
                return std::nullopt;
            }

            discriminant = sqrt(discriminant);
            double t0 = (-b - discriminant) / (2 * a);
            double t1 = (-b + discriminant) / (2 * a);

            return ((a > 0.0) ? std::make_pair(t0, t1) : std::make_pair(t1, t0));
        }
    }
}

#endif // ARMORIAL_UTILS_H
