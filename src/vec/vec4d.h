#pragma once

#include "core/constants.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace lmath {

    struct Vec4d {
        double x;
        double y;
        double z;
        double w;

        constexpr Vec4d() noexcept : x(0.0), y(0.0), z(0.0), w(0.0) {}

        constexpr Vec4d(double vx, double vy, double vz, double vw) noexcept
            : x(vx), y(vy), z(vz), w(vw) {
        }

        explicit constexpr Vec4d(double v) noexcept : x(v), y(v), z(v), w(v) {}

        constexpr double& operator[](std::size_t i) noexcept {
            static_assert(sizeof(Vec4d) == 4 * sizeof(double));
            return (&x)[i];
        }

        constexpr const double& operator[](std::size_t i) const noexcept {
            static_assert(sizeof(Vec4d) == 4 * sizeof(double));
            return (&x)[i];
        }

        constexpr Vec4d operator+() const noexcept { return *this; }

        constexpr Vec4d operator-() const noexcept { return Vec4d(-x, -y, -z, -w); }

        constexpr Vec4d& operator+=(const Vec4d& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        constexpr Vec4d& operator-=(const Vec4d& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }

        constexpr Vec4d& operator*=(double s) noexcept {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }

        constexpr Vec4d& operator/=(double s) noexcept {
            double inv = 1.0 / s;
            x *= inv;
            y *= inv;
            z *= inv;
            w *= inv;
            return *this;
        }

        constexpr double length_sq() const noexcept {
            return x * x + y * y + z * z + w * w;
        }

        double length() const noexcept {
            return std::sqrt(length_sq());
        }

        Vec4d normalized() const noexcept;
        Vec4d& normalize() noexcept;
        bool try_normalize(double eps = epsilon_d) noexcept;
    };

    constexpr Vec4d operator+(const Vec4d& a, const Vec4d& b) noexcept;
    constexpr Vec4d operator-(const Vec4d& a, const Vec4d& b) noexcept;
    constexpr Vec4d operator*(const Vec4d& v, double s) noexcept;
    constexpr Vec4d operator*(double s, const Vec4d& v) noexcept;
    constexpr Vec4d operator/(const Vec4d& v, double s) noexcept;

    inline Vec4d Vec4d::normalized() const noexcept {
        double len = length();
        return (*this) / len;
    }

    inline Vec4d& Vec4d::normalize() noexcept {
        double len = length();
        return (*this) /= len;
    }

    inline bool Vec4d::try_normalize(double eps) noexcept {
        double len_sq = length_sq();
        if (len_sq <= eps * eps) {
            return false;
        }
        double inv_len = 1.0 / std::sqrt(len_sq);
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
        w *= inv_len;
        return true;
    }

    constexpr Vec4d operator+(const Vec4d& a, const Vec4d& b) noexcept {
        return Vec4d(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    constexpr Vec4d operator-(const Vec4d& a, const Vec4d& b) noexcept {
        return Vec4d(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    constexpr Vec4d operator*(const Vec4d& v, double s) noexcept {
        return Vec4d(v.x * s, v.y * s, v.z * s, v.w * s);
    }

    constexpr Vec4d operator*(double s, const Vec4d& v) noexcept {
        return v * s;
    }

    constexpr Vec4d operator/(const Vec4d& v, double s) noexcept {
        return Vec4d(v.x / s, v.y / s, v.z / s, v.w / s);
    }

    constexpr double dot(const Vec4d& a, const Vec4d& b) noexcept {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    constexpr bool operator==(const Vec4d& a, const Vec4d& b) noexcept {
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }

    constexpr bool operator!=(const Vec4d& a, const Vec4d& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_vec<Vec4d> : std::true_type {};

}  // namespace lmath