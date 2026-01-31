#pragma once

#include "core/constants.h"
#include "vec/vec2f.h"

namespace lmath {

    struct Mat2f {
        Vec2f col0;
        Vec2f col1;

        constexpr Mat2f() noexcept : col0(1.0f, 0.0f), col1(0.0f, 1.0f) {}

        constexpr Mat2f(const Vec2f& c0, const Vec2f& c1) noexcept : col0(c0), col1(c1) {}

        constexpr explicit Mat2f(float s) noexcept : col0(s, 0.0f), col1(0.0f, s) {}

        constexpr const Vec2f& operator[](std::size_t i) const noexcept {
            return (&col0)[i];
        }

        constexpr Vec2f& operator[](std::size_t i) noexcept {
            return (&col0)[i];
        }
    };

    constexpr Vec2f operator*(const Mat2f& m, const Vec2f& v) noexcept {
        return v.x * m.col0 + v.y * m.col1;
    }

    constexpr Mat2f operator*(const Mat2f& a, const Mat2f& b) noexcept {
        return Mat2f(a * b.col0, a * b.col1);
    }

    constexpr Mat2f transpose(const Mat2f& m) noexcept {
        return Mat2f(Vec2f(m.col0.x, m.col1.x), Vec2f(m.col0.y, m.col1.y));
    }

    constexpr float determinant(const Mat2f& m) noexcept {
        return m.col0.x * m.col1.y - m.col1.x * m.col0.y;
    }

    constexpr Mat2f inverse(const Mat2f& m) noexcept {
        float det = determinant(m);
        float inv_det = 1.0f / det;
        return Mat2f(Vec2f(m.col1.y * inv_det, -m.col0.y * inv_det),
            Vec2f(-m.col1.x * inv_det, m.col0.x * inv_det));
    }

    constexpr bool operator==(const Mat2f& a, const Mat2f& b) noexcept {
        return a.col0 == b.col0 && a.col1 == b.col1;
    }

    constexpr bool operator!=(const Mat2f& a, const Mat2f& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_mat<Mat2f> : std::true_type {};

}  // namespace lmath