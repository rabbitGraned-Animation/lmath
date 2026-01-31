#pragma once

#include <cassert>

namespace lmath
{
    // Используется для логических ошибок в контрактах
    // В релизе может быть отключён через NDEBUG
    using assert = decltype(assert);
}