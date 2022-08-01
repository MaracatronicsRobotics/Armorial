#ifndef ARMORIAL_TYPES_TRAITS_H
#define ARMORIAL_TYPES_TRAITS_H

#include <type_traits>

namespace Types {

/*!
 * \brief Check if the given type T is iterable.
 */
template <typename T, typename = void>
struct is_iterable : std::false_type { };

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>> : std::true_type { };

template <class T>
inline static constexpr bool is_iterable_v = is_iterable<T>::value;

/*!
 * \brief Check if the given type T has coordinate getters (.x() and .y())
 */
template <typename T, typename = void>
struct has_coordinates : std::false_type { };

template <typename T>
struct has_coordinates<T, std::void_t<decltype(std::declval<T>().x()), decltype(std::declval<T>().y())>> : std::true_type { };

template <class T>
inline static constexpr bool has_coordinates_v = has_coordinates<T>::value;

}

#endif // TRAITS_H
