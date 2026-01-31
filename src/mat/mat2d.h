#pragma once

#include "core/constants.h"
#include "vec/vec2d.h"

namespace lmath {

    struct Mat2d {
        Vec2d col0;
        Vec2d col1;

        constexpr Mat2d() noexcept : col0(1.0, 0.0), col1(0.0, 1.0) {}

        constexpr Mat2d(const Vec2d& c0, const Vec2d& c1) noexcept : col0(c0), col1(c1) {}

        constexpr explicit Mat2d(double s) noexcept : col0(s, 0.0), col1(0.0, s) {}

        constexpr const Vec2d& operator[](std::size_t i) const noexcept {
            return (&col0)[i];
        }

        constexpr Vec2d& operator[](std::size_t i) noexcept {
            return (&col0)[i];
        }
    };

    constexpr Vec2d operator*(const Mat2d& m, const Vec2d& v) noexcept {
        return v.x * m.col0 + v.y * m.col1;
    }

    constexpr Mat2d operator*(const Mat2d& a, const Mat2d& b) noexcept {
        return Mat2d(a * b.col0, a * b.col1);
    }

    constexpr Mat2d transpose(const Mat2d& m) noexcept {
        return Mat2d(Vec2d(m.col0.x, m.col1.x), Vec2d(m.col0.y, m.col1.y));
    }

    constexpr double determinant(const Mat2d& m) noexcept {
        return m.col0.x * m.col1.y - m.col1.x * m.col0.y;
    }

    constexpr Mat2d inverse(const Mat2d& m) noexcept {
        double det = determinant(m);
        double inv_det = 1.0 / det;
        return Mat2d(Vec2d(m.col1.y * inv_det, -m.col0.y * inv_det),
            Vec2d(-m.col1.x * inv_det, m.col0.x * inv_det));
    }

    constexpr bool operator==(const Mat2d& a, const Mat2d& b) noexcept {
        return a.col0 == b.col0 && a.col1 == b.col1;
    }

    constexpr bool operator!=(const Mat2d& a, const Mat2d& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_mat<Mat2d> : std::true_type {};

}  // namespace lmath