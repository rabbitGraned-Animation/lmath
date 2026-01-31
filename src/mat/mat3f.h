#pragma once

#include "core/constants.h"
#include "vec/vec3f.h"

namespace lmath {

    struct Mat3f {
        Vec3f col0;
        Vec3f col1;
        Vec3f col2;

        constexpr Mat3f() noexcept
            : col0(1.0f, 0.0f, 0.0f),
            col1(0.0f, 1.0f, 0.0f),
            col2(0.0f, 0.0f, 1.0f) {
        }

        constexpr Mat3f(const Vec3f& c0, const Vec3f& c1, const Vec3f& c2) noexcept
            : col0(c0), col1(c1), col2(c2) {
        }

        constexpr explicit Mat3f(float s) noexcept
            : col0(s, 0.0f, 0.0f),
            col1(0.0f, s, 0.0f),
            col2(0.0f, 0.0f, s) {
        }

        constexpr const Vec3f& operator[](std::size_t i) const noexcept {
            return (&col0)[i];
        }

        constexpr Vec3f& operator[](std::size_t i) noexcept {
            return (&col0)[i];
        }
    };

    constexpr Vec3f operator*(const Mat3f& m, const Vec3f& v) noexcept {
        return v.x * m.col0 + v.y * m.col1 + v.z * m.col2;
    }

    constexpr Mat3f operator*(const Mat3f& a, const Mat3f& b) noexcept {
        return Mat3f(a * b.col0, a * b.col1, a * b.col2);
    }

    constexpr Mat3f transpose(const Mat3f& m) noexcept {
        return Mat3f(Vec3f(m.col0.x, m.col1.x, m.col2.x),
            Vec3f(m.col0.y, m.col1.y, m.col2.y),
            Vec3f(m.col0.z, m.col1.z, m.col2.z));
    }

    constexpr float determinant(const Mat3f& m) noexcept {
        return dot(m.col0, cross(m.col1, m.col2));
    }

    constexpr Mat3f inverse(const Mat3f& m) noexcept {
        float det = determinant(m);
        float inv_det = 1.0f / det;
        Vec3f c0 = cross(m.col1, m.col2) * inv_det;
        Vec3f c1 = cross(m.col2, m.col0) * inv_det;
        Vec3f c2 = cross(m.col0, m.col1) * inv_det;
        return Mat3f(
            Vec3f(c0.x, c1.x, c2.x),
            Vec3f(c0.y, c1.y, c2.y),
            Vec3f(c0.z, c1.z, c2.z)
        );
    }

    constexpr bool operator==(const Mat3f& a, const Mat3f& b) noexcept {
        return a.col0 == b.col0 && a.col1 == b.col1 && a.col2 == b.col2;
    }

    constexpr bool operator!=(const Mat3f& a, const Mat3f& b) noexcept {
        return !(a == b);
    }

    template <>
    struct is_mat<Mat3f> : std::true_type {};

}  // namespace lmath