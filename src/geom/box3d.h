/*
* lmath library
* License: BSD 3-Clause License
*
* Copyright "rabbitGraned Animation"
*/

#pragma once

#include "vec/vec3d.h"

#include <limits>
#include <cassert>

namespace lmath {

    struct Box3d
    {
        Vec3d min;
        Vec3d max;

        constexpr Box3d() noexcept
            : min(std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()),
            max(-std::numeric_limits<double>::max(),
                -std::numeric_limits<double>::max(),
                -std::numeric_limits<double>::max()) {
        }

        constexpr Box3d(const Vec3d& point) noexcept
            : min(point), max(point) {
        }

        constexpr Box3d(const Vec3d& vmin, const Vec3d& vmax) noexcept
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

        constexpr void extend(const Vec3d& p) noexcept
        {
            min.x = (p.x < min.x) ? p.x : min.x;
            min.y = (p.y < min.y) ? p.y : min.y;
            min.z = (p.z < min.z) ? p.z : min.z;
            max.x = (p.x > max.x) ? p.x : max.x;
            max.y = (p.y > max.y) ? p.y : max.y;
            max.z = (p.z > max.z) ? p.z : max.z;
        }

        constexpr void extend(const Box3d& b) noexcept
        {
            if (!b.empty())
            {
                extend(b.min);
                extend(b.max);
            }
        }

        constexpr Vec3d center() const noexcept
        {
            return (min + max) * 0.5;
        }

        constexpr Vec3d size() const noexcept
        {
            return max - min;
        }
    };

    constexpr bool operator==(const Box3d& a, const Box3d& b) noexcept
    {
        return a.min == b.min && a.max == b.max;
    }

    constexpr bool operator!=(const Box3d& a, const Box3d& b) noexcept
    {
        return !(a == b);
    }

}  // namespace lmath