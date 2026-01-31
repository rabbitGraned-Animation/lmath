#pragma once

#include "core/constants.h"
#include "vec/vec3d.h"

namespace lmath {

    struct Mat3d {
        Vec3d col0;
        Vec3d col1;
        Vec3d col2;

        constexpr Mat3d() noexcept
            : col0(1.0, 0.0, 0.0),
            col1(0.0, 1.0, 0.0),
            col2(0.0, 0.0, 1.0) {
        }

        constexpr Mat3d(const Vec3d& c0, const Vec3d& c1, const Vec3d& c2) noexcept
            : col0(c0), col1(c1), col2(c2) {
        }

        constexpr explicit Mat3d(double s) noexcept
            : col0(s, 0.0, 0.0),
            col1(0.0, s, 0.0),
            col2(0.0, 0.0, s) {
        }

        constexpr const Vec3d& operator[](std::size_t i) const noexcept {
            return (&col0)[i];
        }

        constexpr Vec3d& operator[](std::size_t i) noexcept {
            return (&col0)[i];
        }
    };

    constexpr Vec3d operator*(const Mat3d& m, const Vec3d& v) noexcept {
        return v.x * m.col0 + v.y * m.col1 + v.z * m.col2;
    }

    constexpr Mat3d operator*(const Mat3d& a, const Mat3d& b) noexcept {
        return Mat3d(a * b.col0, a * b.col1, a * b.col2);
    }

    constexpr Mat3d transpose(const Mat3d& m) noexcept {
        return Mat3d(Vec3d(m.col0.x, m.col1.x, m.col2.x),
            Vec3d(m.col0.y, m.col1.y, m.col2.y),
            Vec3d(m.col0.z, m.col1.z, m.col2.z));
    }

    constexpr double determinant(const Mat3d& m) noexcept {
        return dot(m.col0, cross(m.col1, m.col2));
    }

    constexpr Mat3d inverse(const Mat3d& m) noexcept {
        double det = determinant(m);
        double inv_det = 1.0 / det;
        Vec3d c0 = cross(m.col1, m.col2) * inv_det;
        Vec3d c1 = cross(m.col2, m.col0) * inv_det;
        Vec3d c2 = cross(m.col0, m.col1) * inv_det;
        return Mat3d(
            Vec3d(c0.x, c1.x, c2.x),
            Vec3d(c0.y, c1.y, c2.y),
            Vec3d(c0.z, c1.z, c2.z)
        );
    }

    constexpr bool operator==(const Mat3d& a, const Mat3d& b) noexcept {
        return a.col0 == b.col0 && a.col1 == b.col1 && a.col2 == b.col2;
    }

    constexpr bool operator!=(const Mat3d& a, const Mat3d& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_mat<Mat3d> : std::true_type {};

}  // namespace lmath