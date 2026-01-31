#pragma once

#include "vec/vec3f.h"

namespace lmath {
    struct Color3f
    {
        float r;
        float g;
        float b;

        constexpr Color3f() noexcept : r(0.0f), g(0.0f), b(0.0f) {}
        constexpr Color3f(float vr, float vg, float vb) noexcept : r(vr), g(vg), b(vb) {}
        explicit constexpr Color3f(float v) noexcept : r(v), g(v), b(v) {}

        constexpr float& operator[](std::size_t i) noexcept
        {
            static_assert(sizeof(Color3f) == 3 * sizeof(float));
            return (&r)[i];
        }

        constexpr const float& operator[](std::size_t i) const noexcept
        {
            static_assert(sizeof(Color3f) == 3 * sizeof(float));
            return (&r)[i];
        }
    };

    constexpr Color3f operator+(Color3f a, const Color3f& b) noexcept { return Color3f(a.r + b.r, a.g + b.g, a.b + b.b); }
    constexpr Color3f operator-(Color3f a, const Color3f& b) noexcept { return Color3f(a.r - b.r, a.g - b.g, a.b - b.b); }
    constexpr Color3f operator*(Color3f c, float s) noexcept { return Color3f(c.r * s, c.g * s, c.b * s); }
    constexpr Color3f operator*(float s, Color3f c) noexcept { return c * s; }
    constexpr Color3f operator/(Color3f c, float s) noexcept { return Color3f(c.r / s, c.g / s, c.b / s); }

    constexpr bool operator==(const Color3f& a, const Color3f& b) noexcept
    {
        return a.r == b.r && a.g == b.g && a.b == b.b;  /*  bitwise equality for half - precision storage   */
    }

    constexpr bool operator!=(const Color3f& a, const Color3f& b) noexcept
    {
        return !(a == b);
    }
}  // namespace lmath