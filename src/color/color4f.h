#pragma once

#include "vec/vec4f.h"

namespace lmath
{
    struct Color4f
    {
        float r;
        float g;
        float b;
        float a;

        constexpr Color4f() noexcept : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
        constexpr Color4f(float vr, float vg, float vb, float va) noexcept : r(vr), g(vg), b(vb), a(va) {}
        constexpr Color4f(const Color3f& rgb, float alpha) noexcept : r(rgb.r), g(rgb.g), b(rgb.b), a(alpha) {}
        explicit constexpr Color4f(float v) noexcept : r(v), g(v), b(v), a(v) {}

        constexpr float& operator[](std::size_t i) noexcept
        {
            static_assert(sizeof(Color4f) == 4 * sizeof(float));
            return (&r)[i];
        }

        constexpr const float& operator[](std::size_t i) const noexcept
        {
            static_assert(sizeof(Color4f) == 4 * sizeof(float));
            return (&r)[i];
        }
    };

    constexpr Color4f operator+(Color4f a, const Color4f& b) noexcept
    {
        return Color4f(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
    }

    constexpr Color4f operator-(Color4f a, const Color4f& b) noexcept
    {
        return Color4f(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);
    }

    constexpr Color4f operator*(Color4f c, float s) noexcept
    {
        return Color4f(c.r * s, c.g * s, c.b * s, c.a * s);
    }

    constexpr Color4f operator*(float s, Color4f c) noexcept { return c * s; }
    constexpr Color4f operator/(Color4f c, float s) noexcept
    {
        return Color4f(c.r / s, c.g / s, c.b / s, c.a / s);
    }

    constexpr bool operator==(const Color4f& a, const Color4f& b) noexcept
    {
        return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;    /*  bitwise equality for half - precision storage   */
    }

    constexpr bool operator!=(const Color4f& a, const Color4f& b) noexcept
    {
        return !(a == b);
    }
}  // namespace lmath