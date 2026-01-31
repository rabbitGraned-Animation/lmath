/*
* lmath library
* License: BSD 3-Clause License
*
* Copyright "rabbitGraned Animation"
*/

#pragma once

#include "core/constants.h"
#include <cmath>

namespace lmath {

    bool approx_equal(float a, float b, float eps = epsilon_f) noexcept {
        return std::abs(a - b) <= eps;
    }

    bool approx_equal(double a, double b, double eps = epsilon_d) noexcept {
        return std::abs(a - b) <= eps;
    }
}  // namespace lmath