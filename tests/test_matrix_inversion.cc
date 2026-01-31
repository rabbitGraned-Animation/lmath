#include "lmath.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <string>

int main()
{
    using namespace lmath;

    std::vector<std::string> failed_components;
    bool all_passed = true;

    auto test_component = [&](const char* name, bool (*test)()) {
        std::cout << name << ": ";
        if (test()) {
            std::cout << "\n\tOK" << std::endl;
            return true;
        }
        else {
            std::cout << "\n\tFAILED" << std::endl;
            failed_components.push_back(name);
            all_passed = false;
            return false;
        }
        };

    // Mat2 inversion
    auto test_mat2_inversion = []() -> bool {
        {
            constexpr Mat2f m(Vec2f(2.0f, 0.0f), Vec2f(0.0f, 3.0f));
            constexpr Mat2f inv = inverse(m);
            constexpr Mat2f identity = m * inv;
            if (!approx_equal(identity.col0.x, 1.0f) ||
                !approx_equal(identity.col0.y, 0.0f) ||
                !approx_equal(identity.col1.x, 0.0f) ||
                !approx_equal(identity.col1.y, 1.0f)) {
                std::cerr << "Mat2f diagonal inversion failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Mat2f m(Vec2f(4.0f, 3.0f), Vec2f(3.0f, 2.0f));
            constexpr float det = determinant(m);
            if (!approx_equal(det, -1.0f)) {
                std::cerr << "Mat2f determinant mismatch" << std::endl;
                return false;
            }
            constexpr Mat2f inv = inverse(m);
            constexpr Mat2f reconstructed = m * inv;
            if (!approx_equal(reconstructed.col0.x, 1.0f) ||
                !approx_equal(reconstructed.col0.y, 0.0f) ||
                !approx_equal(reconstructed.col1.x, 0.0f) ||
                !approx_equal(reconstructed.col1.y, 1.0f)) {
                std::cerr << "Mat2f general inversion failed" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Mat2 inversion", test_mat2_inversion);

    // Mat3 inversion
    auto test_mat3_inversion = []() -> bool {
        {
            constexpr Mat3f m(
                Vec3f(2.0f, 0.0f, 0.0f),
                Vec3f(0.0f, 3.0f, 0.0f),
                Vec3f(0.0f, 0.0f, 4.0f)
            );
            constexpr Mat3f inv = inverse(m);
            constexpr Mat3f identity = m * inv;
            if (!approx_equal(identity.col0.x, 1.0f) || !approx_equal(identity.col0.y, 0.0f) || !approx_equal(identity.col0.z, 0.0f) ||
                !approx_equal(identity.col1.x, 0.0f) || !approx_equal(identity.col1.y, 1.0f) || !approx_equal(identity.col1.z, 0.0f) ||
                !approx_equal(identity.col2.x, 0.0f) || !approx_equal(identity.col2.y, 0.0f) || !approx_equal(identity.col2.z, 1.0f)) {
                std::cerr << "Mat3f diagonal inversion failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Mat3f m(
                Vec3f(1.0f, 2.0f, 3.0f),
                Vec3f(0.0f, 1.0f, 4.0f),
                Vec3f(5.0f, 6.0f, 0.0f)
            );
            constexpr float det = determinant(m);
            if (!approx_equal(det, 1.0f)) {
                std::cerr << "Mat3f determinant mismatch (got " << det << ")" << std::endl;
                return false;
            }
            constexpr Mat3f inv = inverse(m);
            constexpr Mat3f reconstructed = m * inv;
            if (!approx_equal(reconstructed.col0.x, 1.0f) || !approx_equal(reconstructed.col0.y, 0.0f) || !approx_equal(reconstructed.col0.z, 0.0f) ||
                !approx_equal(reconstructed.col1.x, 0.0f) || !approx_equal(reconstructed.col1.y, 1.0f) || !approx_equal(reconstructed.col1.z, 0.0f) ||
                !approx_equal(reconstructed.col2.x, 0.0f) || !approx_equal(reconstructed.col2.y, 0.0f) || !approx_equal(reconstructed.col2.z, 1.0f)) {
                std::cerr << "Mat3f general inversion failed" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Mat3 inversion", test_mat3_inversion);

    // Degenerate cases (contract violation: no crash expected, but result undefined)
    auto test_mat_degenerate = []() -> bool {
        {
            Mat2f m(Vec2f(0.0f, 0.0f), Vec2f(0.0f, 0.0f));
            // This is UB per contract, but we only check that it doesn't crash at runtime
            volatile float d = determinant(m);
            (void)d;
            // Do not inspect result, just ensure program continues
        }
        {
            Mat3f m(
                Vec3f(1.0f, 2.0f, 3.0f),
                Vec3f(1.0f, 2.0f, 3.0f), // duplicate row
                Vec3f(4.0f, 5.0f, 6.0f)
            );
            volatile float d = determinant(m);
            (void)d;
        }
        return true;
        };
    test_component("Degenerate matrices (UB contract)", test_mat_degenerate);

    // Final summary
    std::cout << "\nMatrix Inversion result:" << std::endl;
    if (all_passed) {
        std::cout << "ALL TESTS PASSED" << std::endl;
        return 0;
    }
    else {
        std::cout << "FAILED: ";
        for (size_t i = 0; i < failed_components.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << failed_components[i];
        }
        std::cout << std::endl;
        return 1;
    }
}