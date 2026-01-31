/*
* lmath library
* License: BSD 3-Clause License
*
* Copyright "rabbitGraned Animation"
*/

#pragma once

#include <cmath>

namespace lmath
{
    constexpr float radians(float degrees) noexcept
    {
        return degrees * (3.14159265358979323846f / 180.0f);
    }

    constexpr double radians(double degrees) noexcept
    {
        return degrees * (3.14159265358979323846 / 180.0);
    }

    constexpr float degrees(float radians) noexcept
    {
        return radians * (180.0f / 3.14159265358979323846f);
    }

    constexpr double degrees(double radians) noexcept
    {
        return radians * (180.0 / 3.14159265358979323846);
    }

    constexpr float clamp(float v, float lo, float hi) noexcept
    {
        return (v < lo) ? lo : (v > hi) ? hi : v;
    }

    constexpr double clamp(double v, double lo, double hi) noexcept
    {
        return (v < lo) ? lo : (v > hi) ? hi : v;
    }
}