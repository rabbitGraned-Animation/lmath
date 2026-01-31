#pragma once

#include "core/constants.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace lmath {

    struct Vec4f {
        float x;
        float y;
        float z;
        float w;

        constexpr Vec4f() noexcept : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

        constexpr Vec4f(float vx, float vy, float vz, float vw) noexcept
            : x(vx), y(vy), z(vz), w(vw) {
        }

        explicit constexpr Vec4f(float v) noexcept : x(v), y(v), z(v), w(v) {}

        constexpr float& operator[](std::size_t i) noexcept {
            static_assert(sizeof(Vec4f) == 4 * sizeof(float));
            return (&x)[i];
        }

        constexpr const float& operator[](std::size_t i) const noexcept {
            static_assert(sizeof(Vec4f) == 4 * sizeof(float));
            return (&x)[i];
        }

        constexpr Vec4f operator+() const noexcept { return *this; }

        constexpr Vec4f operator-() const noexcept { return Vec4f(-x, -y, -z, -w); }

        constexpr Vec4f& operator+=(const Vec4f& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        constexpr Vec4f& operator-=(const Vec4f& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }

        constexpr Vec4f& operator*=(float s) noexcept {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }

        constexpr Vec4f& operator/=(float s) noexcept {
            float inv = 1.0f / s;
            x *= inv;
            y *= inv;
            z *= inv;
            w *= inv;
            return *this;
        }

        constexpr float length_sq() const noexcept {
            return x * x + y * y + z * z + w * w;
        }

        float length() const noexcept {
            return std::sqrt(length_sq());
        }

        Vec4f normalized() const noexcept;
        Vec4f& normalize() noexcept;
        bool try_normalize(float eps = epsilon_f) noexcept;
    };

    constexpr Vec4f operator+(const Vec4f& a, const Vec4f& b) noexcept;
    constexpr Vec4f operator-(const Vec4f& a, const Vec4f& b) noexcept;
    constexpr Vec4f operator*(const Vec4f& v, float s) noexcept;
    constexpr Vec4f operator*(float s, const Vec4f& v) noexcept;
    constexpr Vec4f operator/(const Vec4f& v, float s) noexcept;

    inline Vec4f Vec4f::normalized() const noexcept {
        float len = length();
        return (*this) / len;
    }

    inline Vec4f& Vec4f::normalize() noexcept {
        float len = length();
        return (*this) /= len;
    }

    inline bool Vec4f::try_normalize(float eps) noexcept {
        float len_sq = length_sq();
        if (len_sq <= eps * eps) {
            return false;
        }
        float inv_len = 1.0f / std::sqrt(len_sq);
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
        w *= inv_len;
        return true;
    }

    constexpr Vec4f operator+(const Vec4f& a, const Vec4f& b) noexcept {
        return Vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    constexpr Vec4f operator-(const Vec4f& a, const Vec4f& b) noexcept {
        return Vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    constexpr Vec4f operator*(const Vec4f& v, float s) noexcept {
        return Vec4f(v.x * s, v.y * s, v.z * s, v.w * s);
    }

    constexpr Vec4f operator*(float s, const Vec4f& v) noexcept {
        return v * s;
    }

    constexpr Vec4f operator/(const Vec4f& v, float s) noexcept {
        return Vec4f(v.x / s, v.y / s, v.z / s, v.w / s);
    }

    constexpr float dot(const Vec4f& a, const Vec4f& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    constexpr bool operator==(const Vec4f& a, const Vec4f& b) noexcept {
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }

    constexpr bool operator!=(const Vec4f& a, const Vec4f& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_vec<Vec4f> : std::true_type {};

}  // namespace lmath