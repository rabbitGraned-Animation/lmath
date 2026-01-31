#pragma once

#include "core/constants.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace lmath {

    struct Vec3f {
        float x;
        float y;
        float z;

        constexpr Vec3f() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

        constexpr Vec3f(float vx, float vy, float vz) noexcept : x(vx), y(vy), z(vz) {}

        explicit constexpr Vec3f(float v) noexcept : x(v), y(v), z(v) {}

        constexpr float& operator[](std::size_t i) noexcept {
            static_assert(sizeof(Vec3f) == 3 * sizeof(float));
            return (&x)[i];
        }

        constexpr const float& operator[](std::size_t i) const noexcept {
            static_assert(sizeof(Vec3f) == 3 * sizeof(float));
            return (&x)[i];
        }

        constexpr Vec3f operator+() const noexcept { return *this; }

        constexpr Vec3f operator-() const noexcept { return Vec3f(-x, -y, -z); }

        constexpr Vec3f& operator+=(const Vec3f& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        constexpr Vec3f& operator-=(const Vec3f& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        constexpr Vec3f& operator*=(float s) noexcept {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        constexpr Vec3f& operator/=(float s) noexcept {
            float inv = 1.0f / s;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }

        constexpr float length_sq() const noexcept {
            return x * x + y * y + z * z;
        }

        float length() const noexcept {
            return std::sqrt(length_sq());
        }

        Vec3f normalized() const noexcept;
        Vec3f& normalize() noexcept;
        bool try_normalize(float eps = epsilon_f) noexcept;
    };

    constexpr Vec3f operator+(const Vec3f& a, const Vec3f& b) noexcept;
    constexpr Vec3f operator-(const Vec3f& a, const Vec3f& b) noexcept;
    constexpr Vec3f operator*(const Vec3f& v, float s) noexcept;
    constexpr Vec3f operator*(float s, const Vec3f& v) noexcept;
    constexpr Vec3f operator/(const Vec3f& v, float s) noexcept;

    inline Vec3f Vec3f::normalized() const noexcept {
        float len = length();
        return (*this) / len;
    }

    inline Vec3f& Vec3f::normalize() noexcept {
        float len = length();
        return (*this) /= len;
    }

    inline bool Vec3f::try_normalize(float eps) noexcept {
        float len_sq = length_sq();
        if (len_sq <= eps * eps) {
            return false;
        }
        float inv_len = 1.0f / std::sqrt(len_sq);
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
        return true;
    }

    constexpr Vec3f operator+(const Vec3f& a, const Vec3f& b) noexcept {
        return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    constexpr Vec3f operator-(const Vec3f& a, const Vec3f& b) noexcept {
        return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    constexpr Vec3f operator*(const Vec3f& v, float s) noexcept {
        return Vec3f(v.x * s, v.y * s, v.z * s);
    }

    constexpr Vec3f operator*(float s, const Vec3f& v) noexcept {
        return v * s;
    }

    constexpr Vec3f operator/(const Vec3f& v, float s) noexcept {
        return Vec3f(v.x / s, v.y / s, v.z / s);
    }

    constexpr float dot(const Vec3f& a, const Vec3f& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    constexpr Vec3f cross(const Vec3f& a, const Vec3f& b) noexcept {
        return Vec3f(a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    constexpr bool operator==(const Vec3f& a, const Vec3f& b) noexcept {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    constexpr bool operator!=(const Vec3f& a, const Vec3f& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_vec<Vec3f> : std::true_type {};

}  // namespace lmath