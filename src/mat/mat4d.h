#pragma once

#include "core/constants.h"
#include "vec/vec4d.h"

namespace lmath {

    struct Mat4d {
        Vec4d col0;
        Vec4d col1;
        Vec4d col2;
        Vec4d col3;

        constexpr Mat4d() noexcept
            : col0(1.0, 0.0, 0.0, 0.0),
            col1(0.0, 1.0, 0.0, 0.0),
            col2(0.0, 0.0, 1.0, 0.0),
            col3(0.0, 0.0, 0.0, 1.0) {
        }

        constexpr Mat4d(const Vec4d& c0, const Vec4d& c1, const Vec4d& c2, const Vec4d& c3) noexcept
            : col0(c0), col1(c1), col2(c2), col3(c3) {
        }

        constexpr explicit Mat4d(double s) noexcept
            : col0(s, 0.0, 0.0, 0.0),
            col1(0.0, s, 0.0, 0.0),
            col2(0.0, 0.0, s, 0.0),
            col3(0.0, 0.0, 0.0, s) {
        }

        constexpr const Vec4d& operator[](std::size_t i) const noexcept {
            return (&col0)[i];
        }

        constexpr Vec4d& operator[](std::size_t i) noexcept {
            return (&col0)[i];
        }
    };

    constexpr Vec4d operator*(const Mat4d& m, const Vec4d& v) noexcept {
        return v.x * m.col0 + v.y * m.col1 + v.z * m.col2 + v.w * m.col3;
    }

    constexpr Mat4d operator*(const Mat4d& a, const Mat4d& b) noexcept {
        return Mat4d(a * b.col0, a * b.col1, a * b.col2, a * b.col3);
    }

    constexpr Mat4d transpose(const Mat4d& m) noexcept {
        return Mat4d(Vec4d(m.col0.x, m.col1.x, m.col2.x, m.col3.x),
            Vec4d(m.col0.y, m.col1.y, m.col2.y, m.col3.y),
            Vec4d(m.col0.z, m.col1.z, m.col2.z, m.col3.z),
            Vec4d(m.col0.w, m.col1.w, m.col2.w, m.col3.w));
    }

    constexpr double determinant(const Mat4d& m) noexcept {
        double det =
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

    constexpr Mat4d inverse(const Mat4d& m) noexcept {
        double det = determinant(m);
        double inv_det = 1.0 / det;

        Vec4d col0(
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

        Vec4d col1(
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

        Vec4d col2(
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

        Vec4d col3(
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

        return Mat4d(col0, col1, col2, col3);
    }

    constexpr bool operator==(const Mat4d& a, const Mat4d& b) noexcept {
        return a.col0 == b.col0 && a.col1 == b.col1 && a.col2 == b.col2 && a.col3 == b.col3;
    }

    constexpr bool operator!=(const Mat4d& a, const Mat4d& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_mat<Mat4d> : std::true_type {};

}  // namespace lmath