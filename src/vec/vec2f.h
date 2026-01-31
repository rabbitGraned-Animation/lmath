#pragma once

#include "core/constants.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace lmath {

    struct Vec2f {
        float x;
        float y;

        constexpr Vec2f() noexcept : x(0.0f), y(0.0f) {}

        constexpr Vec2f(float vx, float vy) noexcept : x(vx), y(vy) {}

        explicit constexpr Vec2f(float v) noexcept : x(v), y(v) {}

        constexpr float& operator[](std::size_t i) noexcept {
            static_assert(sizeof(Vec2f) == 2 * sizeof(float));
            return (&x)[i];
        }

        constexpr const float& operator[](std::size_t i) const noexcept {
            static_assert(sizeof(Vec2f) == 2 * sizeof(float));
            return (&x)[i];
        }

        constexpr Vec2f operator+() const noexcept { return *this; }

        constexpr Vec2f operator-() const noexcept { return Vec2f(-x, -y); }

        constexpr Vec2f& operator+=(const Vec2f& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        constexpr Vec2f& operator-=(const Vec2f& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        constexpr Vec2f& operator*=(float s) noexcept {
            x *= s;
            y *= s;
            return *this;
        }

        constexpr Vec2f& operator/=(float s) noexcept {
            float inv = 1.0f / s;
            x *= inv;
            y *= inv;
            return *this;
        }

        constexpr float length_sq() const noexcept {
            return x * x + y * y;
        }

        float length() const noexcept {
            return std::sqrt(length_sq());
        }

        Vec2f normalized() const noexcept;
        Vec2f& normalize() noexcept;
        bool try_normalize(float eps = epsilon_f) noexcept;
    };

    constexpr Vec2f operator+(const Vec2f& a, const Vec2f& b) noexcept;
    constexpr Vec2f operator-(const Vec2f& a, const Vec2f& b) noexcept;
    constexpr Vec2f operator*(const Vec2f& v, float s) noexcept;
    constexpr Vec2f operator*(float s, const Vec2f& v) noexcept;
    constexpr Vec2f operator/(const Vec2f& v, float s) noexcept;

    inline Vec2f Vec2f::normalized() const noexcept {
        float len = length();
        return (*this) / len;
    }

    inline Vec2f& Vec2f::normalize() noexcept {
        float len = length();
        return (*this) /= len;
    }

    inline bool Vec2f::try_normalize(float eps) noexcept {
        float len_sq = length_sq();
        if (len_sq <= eps * eps) {
            return false;
        }
        float inv_len = 1.0f / std::sqrt(len_sq);
        x *= inv_len;
        y *= inv_len;
        return true;
    }

    constexpr Vec2f operator+(const Vec2f& a, const Vec2f& b) noexcept {
        return Vec2f(a.x + b.x, a.y + b.y);
    }

    constexpr Vec2f operator-(const Vec2f& a, const Vec2f& b) noexcept {
        return Vec2f(a.x - b.x, a.y - b.y);
    }

    constexpr Vec2f operator*(const Vec2f& v, float s) noexcept {
        return Vec2f(v.x * s, v.y * s);
    }

    constexpr Vec2f operator*(float s, const Vec2f& v) noexcept {
        return v * s;
    }

    constexpr Vec2f operator/(const Vec2f& v, float s) noexcept {
        return Vec2f(v.x / s, v.y / s);
    }

    constexpr float dot(const Vec2f& a, const Vec2f& b) noexcept {
        return a.x * b.x + a.y * b.y;
    }

    constexpr bool operator==(const Vec2f& a, const Vec2f& b) noexcept {
        return a.x == b.x && a.y == b.y;
    }

    constexpr bool operator!=(const Vec2f& a, const Vec2f& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_vec<Vec2f> : std::true_type {};

}  // namespace lmath