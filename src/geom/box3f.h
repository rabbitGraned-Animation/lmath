/*
* lmath library
* License: BSD 3-Clause License
*
* Copyright "rabbitGraned Animation"
*/

#pragma once

#include "core/constants.h"
#include "vec/vec3f.h"

#include <limits>
#include <cassert>

namespace lmath {

    struct Box3f
    {
        Vec3f min;
        Vec3f max;

        constexpr Box3f() noexcept
            : min(std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max()),
            max(-std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max()) {
        }

        constexpr Box3f(const Vec3f& point) noexcept
            : min(point), max(point) {
        }

        constexpr Box3f(const Vec3f& vmin, const Vec3f& vmax) noexcept
            : min(vmin), max(vmax) {
        }

        constexpr bool empty() const noexcept
        {
            return min.x > max.x || min.y > max.y || min.z > max.z;
        }

        constexpr bool is_valid() const noexcept
        {
            return !empty();
        }

        constexpr void extend(const Vec3f& p) noexcept
        {
            min.x = (p.x < min.x) ? p.x : min.x;
            min.y = (p.y < min.y) ? p.y : min.y;
            min.z = (p.z < min.z) ? p.z : min.z;
            max.x = (p.x > max.x) ? p.x : max.x;
            max.y = (p.y > max.y) ? p.y : max.y;
            max.z = (p.z > max.z) ? p.z : max.z;
        }

        constexpr void extend(const Box3f& b) noexcept
        {
            if (!b.empty())
            {
                extend(b.min);
                extend(b.max);
            }
        }

        constexpr Vec3f center() const noexcept
        {
            return (min + max) * 0.5f;
        }

        constexpr Vec3f size() const noexcept
        {
            return max - min;
        }
    };

    constexpr bool operator==(const Box3f& a, const Box3f& b) noexcept
    {
        return a.min == b.min && a.max == b.max;
    }

    constexpr bool operator!=(const Box3f& a, const Box3f& b) noexcept
    {
        return !(a == b);
    }

}  // namespace lmath