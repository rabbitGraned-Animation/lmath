#pragma once

#include <cstdint>

namespace lmath {
    struct half
    {
        uint16_t data;

        constexpr half() noexcept : data(0) {}
        explicit constexpr half(uint16_t v) noexcept : data(v) {}
    };

    static_assert(sizeof(half) == 2);
    static_assert(alignof(half) == 2);
}  // namespace lmath