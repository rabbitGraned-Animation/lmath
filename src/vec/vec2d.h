#pragma once

#include "core/constants.h"

#include <cmath>
#include <cassert>
#include <cstddef>

namespace lmath {

    struct Vec2d {
        double x;
        double y;

        constexpr Vec2d() noexcept : x(0.0), y(0.0) {}

        constexpr Vec2d(double vx, double vy) noexcept : x(vx), y(vy) {}

        explicit constexpr Vec2d(double v) noexcept : x(v), y(v) {}

        constexpr double& operator[](std::size_t i) noexcept {
            static_assert(sizeof(Vec2d) == 2 * sizeof(double));
            return (&x)[i];
        }

        constexpr const double& operator[](std::size_t i) const noexcept {
            static_assert(sizeof(Vec2d) == 2 * sizeof(double));
            return (&x)[i];
        }

        constexpr Vec2d operator+() const noexcept { return *this; }

        constexpr Vec2d operator-() const noexcept { return Vec2d(-x, -y); }

        constexpr Vec2d& operator+=(const Vec2d& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        constexpr Vec2d& operator-=(const Vec2d& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        constexpr Vec2d& operator*=(double s) noexcept {
            x *= s;
            y *= s;
            return *this;
        }

        constexpr Vec2d& operator/=(double s) noexcept {
            double inv = 1.0 / s;
            x *= inv;
            y *= inv;
            return *this;
        }

        constexpr double length_sq() const noexcept {
            return x * x + y * y;
        }

        double length() const noexcept {
            return std::sqrt(length_sq());
        }

        Vec2d normalized() const noexcept;
        Vec2d& normalize() noexcept;
        bool try_normalize(double eps = epsilon_d) noexcept;
    };

    constexpr Vec2d operator+(const Vec2d& a, const Vec2d& b) noexcept;
    constexpr Vec2d operator-(const Vec2d& a, const Vec2d& b) noexcept;
    constexpr Vec2d operator*(const Vec2d& v, double s) noexcept;
    constexpr Vec2d operator*(double s, const Vec2d& v) noexcept;
    constexpr Vec2d operator/(const Vec2d& v, double s) noexcept;

    inline Vec2d Vec2d::normalized() const noexcept {
        double len = length();
        return (*this) / len;
    }

    inline Vec2d& Vec2d::normalize() noexcept {
        double len = length();
        return (*this) /= len;
    }

    inline bool Vec2d::try_normalize(double eps) noexcept {
        double len_sq = length_sq();
        if (len_sq <= eps * eps) {
            return false;
        }
        double inv_len = 1.0 / std::sqrt(len_sq);
        x *= inv_len;
        y *= inv_len;
        return true;
    }

    constexpr Vec2d operator+(const Vec2d& a, const Vec2d& b) noexcept {
        return Vec2d(a.x + b.x, a.y + b.y);
    }

    constexpr Vec2d operator-(const Vec2d& a, const Vec2d& b) noexcept {
        return Vec2d(a.x - b.x, a.y - b.y);
    }

    constexpr Vec2d operator*(const Vec2d& v, double s) noexcept {
        return Vec2d(v.x * s, v.y * s);
    }

    constexpr Vec2d operator*(double s, const Vec2d& v) noexcept {
        return v * s;
    }

    constexpr Vec2d operator/(const Vec2d& v, double s) noexcept {
        return Vec2d(v.x / s, v.y / s);
    }

    constexpr double dot(const Vec2d& a, const Vec2d& b) noexcept {
        return a.x * b.x + a.y * b.y;
    }

    constexpr bool operator==(const Vec2d& a, const Vec2d& b) noexcept {
        return a.x == b.x && a.y == b.y;
    }

    constexpr bool operator!=(const Vec2d& a, const Vec2d& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_vec<Vec2d> : std::true_type {};

}  // namespace lmath