#pragma once

#include <type_traits>

namespace lmath {
    template<typename T>
    struct is_vec : std::false_type {};

    template<typename T>
    struct is_mat : std::false_type {};

    template<typename T>
    struct is_quat : std::false_type {};

    template<typename T>
    inline constexpr bool is_vec_v = is_vec<T>::value;

    template<typename T>
    inline constexpr bool is_mat_v = is_mat<T>::value;

    template<typename T>
    inline constexpr bool is_quat_v = is_quat<T>::value;
}  // namespace lmath