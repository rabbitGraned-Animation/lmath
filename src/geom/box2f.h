/*
* lmath library
* License: BSD 3-Clause License
*
* Copyright "rabbitGraned Animation"
*/

#pragma once

#include "core/constants.h"
#include "vec/vec2f.h"

#include <cassert>

namespace lmath {

    struct Box2f
    {
        Vec2f min;
        Vec2f max;

        constexpr Box2f() noexcept
            : min(std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max()),
            max(-std::numeric_limits<float>::max(),
                -std::numeric_limits<float>::max()) {
        }

        constexpr Box2f(const Vec2f& point) noexcept
            : min(point), max(point) {
        }

        constexpr Box2f(const Vec2f& vmin, const Vec2f& vmax) noexcept
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

        constexpr void extend(const Vec2f& p) noexcept
        {
            min.x = (p.x < min.x) ? p.x : min.x;
            min.y = (p.y < min.y) ? p.y : min.y;
            max.x = (p.x > max.x) ? p.x : max.x;
            max.y = (p.y > max.y) ? p.y : max.y;
        }

        constexpr void extend(const Box2f& b) noexcept
        {
            if (!b.empty())
            {
                extend(b.min);
                extend(b.max);
            }
        }

        constexpr Vec2f center() const noexcept
        {
            return (min + max) * 0.5f;
        }

        constexpr Vec2f size() const noexcept
        {
            return max - min;
        }
    };

    constexpr bool operator==(const Box2f& a, const Box2f& b) noexcept
    {
        return a.min == b.min && a.max == b.max;
    }

    constexpr bool operator!=(const Box2f& a, const Box2f& b) noexcept
    {
        return !(a == b);
    }

}  // namespace lmath