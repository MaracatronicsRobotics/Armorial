#ifndef ARMORIAL_UTILS_H
#define ARMORIAL_UTILS_H

#include <QNetworkDatagram>

#include <math.h>

namespace Utils {
    namespace Proto {
        /*!
         * \tparam T The type of the protobuf object that the network datagram will be converted to
         * \brief Convert a QNetworkDatagram to the protobuf type T
         * \param datagram The reference for the QNetworkDatagram object
         * \param type The reference for the object of type T
         */
        template <typename T>
        [[nodiscard]] static constexpr bool convertDatagramToType(QNetworkDatagram &datagram, T& type) noexcept {
            return (type.ParseFromArray(datagram.data().data(), datagram.data().size()));
        }
    }

    namespace Algebra {
        std::optional<std::pair<double, double>> solveQuadratic(double a, double b, double c) {
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
