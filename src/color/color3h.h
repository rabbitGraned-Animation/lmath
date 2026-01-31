#pragma once

#include "core/half.h"

namespace lmath
{
    struct Color3h
    {
        half r;
        half g;
        half b;

        constexpr Color3h() noexcept : r(half{0}), g(half{0}), b(half{0}) {}
        constexpr Color3h(half vr, half vg, half vb) noexcept : r(vr), g(vg), b(vb) {}
        explicit constexpr Color3h(half v) noexcept : r(v), g(v), b(v) {}

        constexpr half& operator[](std::size_t i) noexcept
        {
            static_assert(sizeof(Color3h) == 3 * sizeof(half));
            return (&r)[i];
        }

        constexpr const half& operator[](std::size_t i) const noexcept
        {
            static_assert(sizeof(Color3h) == 3 * sizeof(half));
            return (&r)[i];
        }
    };

    constexpr bool operator==(const Color3h& a, const Color3h& b) noexcept
    {
        return a.r.data == b.r.data && a.g.data == b.g.data && a.b.data == b.b.data;
    }

    constexpr bool operator!=(const Color3h& a, const Color3h& b) noexcept
    {
        return !(a == b);
    }
}  // namespace lmath