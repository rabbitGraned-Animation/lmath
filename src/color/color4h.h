#pragma once

#include "core/half.h"

namespace lmath
{
    struct Color4h
    {
        half r;
        half g;
        half b;
        half a;

        constexpr Color4h() noexcept : r(half{0}), g(half{0}), b(half{0}), a(half{0x3C00}) {} // 1.0 in half
        constexpr Color4h(half vr, half vg, half vb, half va) noexcept : r(vr), g(vg), b(vb), a(va) {}
        explicit constexpr Color4h(half v) noexcept : r(v), g(v), b(v), a(v) {}

        constexpr half& operator[](std::size_t i) noexcept
        {
            static_assert(sizeof(Color4h) == 4 * sizeof(half));
            return (&r)[i];
        }

        constexpr const half& operator[](std::size_t i) const noexcept
        {
            static_assert(sizeof(Color4h) == 4 * sizeof(half));
            return (&r)[i];
        }
    };

    constexpr bool operator==(const Color4h& a, const Color4h& b) noexcept
    {
        return a.r.data == b.r.data && a.g.data == b.g.data && a.b.data == b.b.data && a.a.data == b.a.data;
    }

    constexpr bool operator!=(const Color4h& a, const Color4h& b) noexcept
    {
        return !(a == b);
    }
}  // namespace lmath