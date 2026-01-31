/*
* lmath library
* License: BSD 3-Clause License
*
* Copyright "rabbitGraned Animation"
*/

#pragma once

#include "vec/vec2d.h"

#include <limits>
#include <cassert>

namespace lmath {

    struct Box2d
    {
        Vec2d min;
        Vec2d max;

        constexpr Box2d() noexcept
            : min(std::numeric_limits<double>::max(),
                std::numeric_limits<double>::max()),
            max(-std::numeric_limits<double>::max(),
                -std::numeric_limits<double>::max()) {
        }

        constexpr Box2d(const Vec2d& point) noexcept
            : min(point), max(point) {
        }

        constexpr Box2d(const Vec2d& vmin, const Vec2d& vmax) noexcept
            : min(vmin), max(vmax) {
        }

        constexpr bool empty() const noexcept
        {
            return min.x > max.x || min.y > max.y;
        }

        constexpr bool is_valid() const noexcept
        {
            return !empty();
        }

        constexpr void extend(const Vec2d& p) noexcept
        {
            min.x = (p.x < min.x) ? p.x : min.x;
            min.y = (p.y < min.y) ? p.y : min.y;
            max.x = (p.x > max.x) ? p.x : max.x;
            max.y = (p.y > max.y) ? p.y : max.y;
        }

        constexpr void extend(const Box2d& b) noexcept
        {
            if (!b.empty())
            {
                extend(b.min);
                extend(b.max);
            }
        }

        constexpr Vec2d center() const noexcept
        {
            return (min + max) * 0.5;
        }

        constexpr Vec2d size() const noexcept
        {
            return max - min;
        }
    };

    constexpr bool operator==(const Box2d& a, const Box2d& b) noexcept
    {
        return a.min == b.min && a.max == b.max;
    }

    constexpr bool operator!=(const Box2d& a, const Box2d& b) noexcept
    {
        return !(a == b);
    }

}  // namespace lmath