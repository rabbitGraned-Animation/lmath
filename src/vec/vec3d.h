#pragma once

#include "core/constants.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace lmath {

    struct Vec3d {
        double x;
        double y;
        double z;

        constexpr Vec3d() noexcept : x(0.0), y(0.0), z(0.0) {}

        constexpr Vec3d(double vx, double vy, double vz) noexcept : x(vx), y(vy), z(vz) {}

        explicit constexpr Vec3d(double v) noexcept : x(v), y(v), z(v) {}

        constexpr double& operator[](std::size_t i) noexcept {
            static_assert(sizeof(Vec3d) == 3 * sizeof(double));
            return (&x)[i];
        }

        constexpr const double& operator[](std::size_t i) const noexcept {
            static_assert(sizeof(Vec3d) == 3 * sizeof(double));
            return (&x)[i];
        }

        constexpr Vec3d operator+() const noexcept { return *this; }

        constexpr Vec3d operator-() const noexcept { return Vec3d(-x, -y, -z); }

        constexpr Vec3d& operator+=(const Vec3d& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        constexpr Vec3d& operator-=(const Vec3d& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        constexpr Vec3d& operator*=(double s) noexcept {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        constexpr Vec3d& operator/=(double s) noexcept {
            double inv = 1.0 / s;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }

        constexpr double length_sq() const noexcept {
            return x * x + y * y + z * z;
        }

        double length() const noexcept {
            return std::sqrt(length_sq());
        }

        Vec3d normalized() const noexcept;
        Vec3d& normalize() noexcept;
        bool try_normalize(double eps = epsilon_d) noexcept;
    };

    constexpr Vec3d operator+(const Vec3d& a, const Vec3d& b) noexcept;
    constexpr Vec3d operator-(const Vec3d& a, const Vec3d& b) noexcept;
    constexpr Vec3d operator*(const Vec3d& v, double s) noexcept;
    constexpr Vec3d operator*(double s, const Vec3d& v) noexcept;
    constexpr Vec3d operator/(const Vec3d& v, double s) noexcept;

    inline Vec3d Vec3d::normalized() const noexcept {
        double len = length();
        return (*this) / len;
    }

    inline Vec3d& Vec3d::normalize() noexcept {
        double len = length();
        return (*this) /= len;
    }

    inline bool Vec3d::try_normalize(double eps) noexcept {
        double len_sq = length_sq();
        if (len_sq <= eps * eps) {
            return false;
        }
        double inv_len = 1.0 / std::sqrt(len_sq);
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
        return true;
    }

    constexpr Vec3d operator+(const Vec3d& a, const Vec3d& b) noexcept {
        return Vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    constexpr Vec3d operator-(const Vec3d& a, const Vec3d& b) noexcept {
        return Vec3d(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    constexpr Vec3d operator*(const Vec3d& v, double s) noexcept {
        return Vec3d(v.x * s, v.y * s, v.z * s);
    }

    constexpr Vec3d operator*(double s, const Vec3d& v) noexcept {
        return v * s;
    }

    constexpr Vec3d operator/(const Vec3d& v, double s) noexcept {
        return Vec3d(v.x / s, v.y / s, v.z / s);
    }

    constexpr double dot(const Vec3d& a, const Vec3d& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    constexpr Vec3d cross(const Vec3d& a, const Vec3d& b) noexcept {
        return Vec3d(a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
    }

    constexpr bool operator==(const Vec3d& a, const Vec3d& b) noexcept {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    constexpr bool operator!=(const Vec3d& a, const Vec3d& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_vec<Vec3d> : std::true_type {};

}  // namespace lmath