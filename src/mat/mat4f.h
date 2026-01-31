#pragma once

#include "core/constants.h"
#include "vec/vec4f.h"

namespace lmath {

    struct Mat4f {
        Vec4f col0;
        Vec4f col1;
        Vec4f col2;
        Vec4f col3;

        constexpr Mat4f() noexcept
            : col0(1.0f, 0.0f, 0.0f, 0.0f),
            col1(0.0f, 1.0f, 0.0f, 0.0f),
            col2(0.0f, 0.0f, 1.0f, 0.0f),
            col3(0.0f, 0.0f, 0.0f, 1.0f) {
        }

        constexpr Mat4f(const Vec4f& c0, const Vec4f& c1, const Vec4f& c2, const Vec4f& c3) noexcept
            : col0(c0), col1(c1), col2(c2), col3(c3) {
        }

        constexpr explicit Mat4f(float s) noexcept
            : col0(s, 0.0f, 0.0f, 0.0f),
            col1(0.0f, s, 0.0f, 0.0f),
            col2(0.0f, 0.0f, s, 0.0f),
            col3(0.0f, 0.0f, 0.0f, s) {
        }

        constexpr const Vec4f& operator[](std::size_t i) const noexcept {
            return (&col0)[i];
        }

        constexpr Vec4f& operator[](std::size_t i) noexcept {
            return (&col0)[i];
        }
    };

    constexpr Vec4f operator*(const Mat4f& m, const Vec4f& v) noexcept {
        return v.x * m.col0 + v.y * m.col1 + v.z * m.col2 + v.w * m.col3;
    }

    constexpr Mat4f operator*(const Mat4f& a, const Mat4f& b) noexcept {
        return Mat4f(a * b.col0, a * b.col1, a * b.col2, a * b.col3);
    }

    constexpr Mat4f transpose(const Mat4f& m) noexcept {
        return Mat4f(Vec4f(m.col0.x, m.col1.x, m.col2.x, m.col3.x),
            Vec4f(m.col0.y, m.col1.y, m.col2.y, m.col3.y),
            Vec4f(m.col0.z, m.col1.z, m.col2.z, m.col3.z),
            Vec4f(m.col0.w, m.col1.w, m.col2.w, m.col3.w));
    }

    constexpr float determinant(const Mat4f& m) noexcept {
        float det =
            m.col0.x * (m.col1.y * (m.col2.z * m.col3.w - m.col2.w * m.col3.z) -
                m.col1.z * (m.col2.y * m.col3.w - m.col2.w * m.col3.y) +
                m.col1.w * (m.col2.y * m.col3.z - m.col2.z * m.col3.y))
            - m.col0.y * (m.col1.x * (m.col2.z * m.col3.w - m.col2.w * m.col3.z) -
                m.col1.z * (m.col2.x * m.col3.w - m.col2.w * m.col3.x) +
                m.col1.w * (m.col2.x * m.col3.z - m.col2.z * m.col3.x))
            + m.col0.z * (m.col1.x * (m.col2.y * m.col3.w - m.col2.w * m.col3.y) -
                m.col1.y * (m.col2.x * m.col3.w - m.col2.w * m.col3.x) +
                m.col1.w * (m.col2.x * m.col3.y - m.col2.y * m.col3.x))
            - m.col0.w * (m.col1.x * (m.col2.y * m.col3.z - m.col2.z * m.col3.y) -
                m.col1.y * (m.col2.x * m.col3.z - m.col2.z * m.col3.x) +
                m.col1.z * (m.col2.x * m.col3.y - m.col2.y * m.col3.x));
        return det;
    }

    constexpr Mat4f inverse(const Mat4f& m) noexcept {
        float det = determinant(m);
        float inv_det = 1.0f / det;

        Vec4f col0(
            (m.col1.y * (m.col2.z * m.col3.w - m.col2.w * m.col3.z) -
                m.col1.z * (m.col2.y * m.col3.w - m.col2.w * m.col3.y) +
                m.col1.w * (m.col2.y * m.col3.z - m.col2.z * m.col3.y)) * inv_det,
            -(m.col0.y * (m.col2.z * m.col3.w - m.col2.w * m.col3.z) -
                m.col0.z * (m.col2.y * m.col3.w - m.col2.w * m.col3.y) +
                m.col0.w * (m.col2.y * m.col3.z - m.col2.z * m.col3.y)) * inv_det,
            (m.col0.y * (m.col1.z * m.col3.w - m.col1.w * m.col3.z) -
                m.col0.z * (m.col1.y * m.col3.w - m.col1.w * m.col3.y) +
                m.col0.w * (m.col1.y * m.col3.z - m.col1.z * m.col3.y)) * inv_det,
            -(m.col0.y * (m.col1.z * m.col2.w - m.col1.w * m.col2.z) -
                m.col0.z * (m.col1.y * m.col2.w - m.col1.w * m.col2.y) +
                m.col0.w * (m.col1.y * m.col2.z - m.col1.z * m.col2.y)) * inv_det
        );

        Vec4f col1(
            -(m.col1.x * (m.col2.z * m.col3.w - m.col2.w * m.col3.z) -
                m.col1.z * (m.col2.x * m.col3.w - m.col2.w * m.col3.x) +
                m.col1.w * (m.col2.x * m.col3.z - m.col2.z * m.col3.x)) * inv_det,
            (m.col0.x * (m.col2.z * m.col3.w - m.col2.w * m.col3.z) -
                m.col0.z * (m.col2.x * m.col3.w - m.col2.w * m.col3.x) +
                m.col0.w * (m.col2.x * m.col3.z - m.col2.z * m.col3.x)) * inv_det,
            -(m.col0.x * (m.col1.z * m.col3.w - m.col1.w * m.col3.x) -
                m.col0.z * (m.col1.x * m.col3.w - m.col1.w * m.col3.x) +
                m.col0.w * (m.col1.x * m.col3.z - m.col1.z * m.col3.x)) * inv_det,
            (m.col0.x * (m.col1.z * m.col2.w - m.col1.w * m.col2.z) -
                m.col0.z * (m.col1.x * m.col2.w - m.col1.w * m.col2.x) +
                m.col0.w * (m.col1.x * m.col2.z - m.col1.z * m.col2.x)) * inv_det
        );

        Vec4f col2(
            (m.col1.x * (m.col2.y * m.col3.w - m.col2.w * m.col3.y) -
                m.col1.y * (m.col2.x * m.col3.w - m.col2.w * m.col3.x) +
                m.col1.w * (m.col2.x * m.col3.y - m.col2.y * m.col3.x)) * inv_det,
            -(m.col0.x * (m.col2.y * m.col3.w - m.col2.w * m.col3.y) -
                m.col0.y * (m.col2.x * m.col3.w - m.col2.w * m.col3.x) +
                m.col0.w * (m.col2.x * m.col3.y - m.col2.y * m.col3.x)) * inv_det,
            (m.col0.x * (m.col1.y * m.col3.w - m.col1.w * m.col3.x) -
                m.col0.y * (m.col1.x * m.col3.w - m.col1.w * m.col3.x) +
                m.col0.w * (m.col1.x * m.col3.y - m.col1.y * m.col3.x)) * inv_det,
            -(m.col0.x * (m.col1.y * m.col2.w - m.col1.w * m.col2.x) -
                m.col0.y * (m.col1.x * m.col2.w - m.col1.w * m.col2.x) +
                m.col0.w * (m.col1.x * m.col2.y - m.col1.y * m.col2.x)) * inv_det
        );

        Vec4f col3(
            -(m.col1.x * (m.col2.y * m.col3.z - m.col2.z * m.col3.y) -
                m.col1.y * (m.col2.x * m.col3.z - m.col2.z * m.col3.x) +
                m.col1.z * (m.col2.x * m.col3.y - m.col2.y * m.col3.x)) * inv_det,
            (m.col0.x * (m.col2.y * m.col3.z - m.col2.z * m.col3.y) -
                m.col0.y * (m.col2.x * m.col3.z - m.col2.z * m.col3.x) +
                m.col0.z * (m.col2.x * m.col3.y - m.col2.y * m.col3.x)) * inv_det,
            -(m.col0.x * (m.col1.y * m.col3.z - m.col1.z * m.col3.x) -
                m.col0.y * (m.col1.x * m.col3.z - m.col1.z * m.col3.x) +
                m.col0.z * (m.col1.x * m.col3.y - m.col1.y * m.col3.x)) * inv_det,
            (m.col0.x * (m.col1.y * m.col2.z - m.col1.z * m.col2.x) -
                m.col0.y * (m.col1.x * m.col2.z - m.col1.z * m.col2.x) +
                m.col0.z * (m.col1.x * m.col2.y - m.col1.y * m.col2.x)) * inv_det
        );

        return Mat4f(col0, col1, col2, col3);
    }

    constexpr bool operator==(const Mat4f& a, const Mat4f& b) noexcept {
        return a.col0 == b.col0 && a.col1 == b.col1 && a.col2 == b.col2 && a.col3 == b.col3;
    }

    constexpr bool operator!=(const Mat4f& a, const Mat4f& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_mat<Mat4f> : std::true_type {};

}  // namespace lmath