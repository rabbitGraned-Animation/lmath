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

    // Core types
    auto test_core = []() -> bool {
        static_assert(sizeof(half) == 2, "half size mismatch");
        static_assert(alignof(half) == 2, "half alignment mismatch");
        return true;
        };
    test_component("Core", test_core);

    // Vec sizes and traits
    auto test_vec_traits = []() -> bool {
        static_assert(sizeof(Vec2f) == 2 * sizeof(float), "Vec2f size mismatch");
        static_assert(sizeof(Vec3f) == 3 * sizeof(float), "Vec3f size mismatch");
        static_assert(sizeof(Vec4f) == 4 * sizeof(float), "Vec4f size mismatch");
        static_assert(sizeof(Vec2d) == 2 * sizeof(double), "Vec2d size mismatch");
        static_assert(sizeof(Vec3d) == 3 * sizeof(double), "Vec3d size mismatch");
        static_assert(sizeof(Vec4d) == 4 * sizeof(double), "Vec4d size mismatch");

        static_assert(is_vec_v<Vec2f>, "Vec2f not recognized as vector");
        static_assert(is_vec_v<Vec3f>, "Vec3f not recognized as vector");
        static_assert(is_vec_v<Vec4f>, "Vec4f not recognized as vector");
        static_assert(is_vec_v<Vec2d>, "Vec2d not recognized as vector");
        static_assert(is_vec_v<Vec3d>, "Vec3d not recognized as vector");
        static_assert(is_vec_v<Vec4d>, "Vec4d not recognized as vector");
        static_assert(!is_vec_v<Mat4f>, "Mat4f incorrectly recognized as vector");
        static_assert(!is_vec_v<float>, "float incorrectly recognized as vector");
        return true;
        };
    test_component("Vec traits", test_vec_traits);

    // Matrix sizes and traits
    auto test_mat_traits = []() -> bool {
        static_assert(sizeof(Mat2f) == 4 * sizeof(float), "Mat2f size mismatch");
        static_assert(sizeof(Mat3f) == 9 * sizeof(float), "Mat3f size mismatch");
        static_assert(sizeof(Mat4f) == 16 * sizeof(float), "Mat4f size mismatch");
        static_assert(sizeof(Mat2d) == 4 * sizeof(double), "Mat2d size mismatch");
        static_assert(sizeof(Mat3d) == 9 * sizeof(double), "Mat3d size mismatch");
        static_assert(sizeof(Mat4d) == 16 * sizeof(double), "Mat4d size mismatch");

        static_assert(is_mat_v<Mat2f>, "Mat2f not recognized as matrix");
        static_assert(is_mat_v<Mat3f>, "Mat3f not recognized as matrix");
        static_assert(is_mat_v<Mat4f>, "Mat4f not recognized as matrix");
        static_assert(is_mat_v<Mat2d>, "Mat2d not recognized as matrix");
        static_assert(is_mat_v<Mat3d>, "Mat3d not recognized as matrix");
        static_assert(is_mat_v<Mat4d>, "Mat4d not recognized as matrix");
        static_assert(!is_mat_v<Vec3f>, "Vec3f incorrectly recognized as matrix");
        static_assert(!is_mat_v<float>, "float incorrectly recognized as matrix");
        return true;
        };
    test_component("Mat traits", test_mat_traits);

    // Quat traits
    auto test_quat_traits = []() -> bool {
        static_assert(sizeof(Quatf) == 4 * sizeof(float), "Quatf size mismatch");
        static_assert(sizeof(Quatd) == 4 * sizeof(double), "Quatd size mismatch");

        static_assert(is_quat_v<Quatf>, "Quatf not recognized as quaternion");
        static_assert(is_quat_v<Quatd>, "Quatd not recognized as quaternion");
        static_assert(!is_quat_v<Vec4f>, "Vec4f incorrectly recognized as quaternion");
        static_assert(!is_quat_v<float>, "float incorrectly recognized as quaternion");
        return true;
        };
    test_component("Quat traits", test_quat_traits);

    // Color sizes
    auto test_color_sizes = []() -> bool {
        static_assert(sizeof(Color3f) == 3 * sizeof(float), "Color3f size mismatch");
        static_assert(sizeof(Color4f) == 4 * sizeof(float), "Color4f size mismatch");
        static_assert(sizeof(Color3h) == 3 * sizeof(half), "Color3h size mismatch");
        static_assert(sizeof(Color4h) == 4 * sizeof(half), "Color4h size mismatch");
        return true;
        };
    test_component("Color sizes", test_color_sizes);

    // Vec constructors
    auto test_vec_constructors = []() -> bool {
        {
            constexpr Vec3f v0;
            if (!(v0.x == 0.0f && v0.y == 0.0f && v0.z == 0.0f)) {
                std::cerr << "default constructor failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f v1(2.0f);
            if (!(v1.x == 2.0f && v1.y == 2.0f && v1.z == 2.0f)) {
                std::cerr << "uniform constructor failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f v2(1.0f, 2.0f, 3.0f);
            if (!(v2.x == 1.0f && v2.y == 2.0f && v2.z == 3.0f)) {
                std::cerr << "component constructor failed" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Vec (constructors)", test_vec_constructors);

    // Vec arithmetic
    auto test_vec_arithmetic = []() -> bool {
        {
            constexpr Vec3f a(1.0f, 2.0f, 3.0f);
            constexpr Vec3f b(1.0f, 1.0f, 1.0f);
            constexpr Vec3f sum = a + b;
            if (!(sum.x == 2.0f && sum.y == 3.0f && sum.z == 4.0f)) {
                std::cerr << "vector addition failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f a(2.0f, 3.0f, 4.0f);
            constexpr Vec3f b(1.0f, 1.0f, 1.0f);
            constexpr Vec3f diff = a - b;
            if (!(diff.x == 1.0f && diff.y == 2.0f && diff.z == 3.0f)) {
                std::cerr << "vector subtraction failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f v(1.0f, 2.0f, 3.0f);
            constexpr Vec3f scaled = v * 2.0f;
            if (!(scaled.x == 2.0f && scaled.y == 4.0f && scaled.z == 6.0f)) {
                std::cerr << "scalar multiplication failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f v(4.0f, 6.0f, 8.0f);
            constexpr Vec3f div = v / 2.0f;
            if (!(div.x == 2.0f && div.y == 3.0f && div.z == 4.0f)) {
                std::cerr << "scalar division failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f a(1.0f, 2.0f, 3.0f);
            constexpr Vec3f b(4.0f, 5.0f, 6.0f);
            if (dot(a, b) != 32.0f) {
                std::cerr << "dot product failed (got " << dot(a, b) << ")" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f x(1.0f, 0.0f, 0.0f);
            constexpr Vec3f y(0.0f, 1.0f, 0.0f);
            constexpr Vec3f z = cross(x, y);
            if (!(z.x == 0.0f && z.y == 0.0f && z.z == 1.0f)) {
                std::cerr << "cross product failed" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Vec operations", test_vec_arithmetic);

    // Mat constructors
    auto test_mat_constructors = []() -> bool {
        constexpr Mat4f m;
        if (!(m.col0.x == 1.0f && m.col0.y == 0.0f && m.col0.z == 0.0f && m.col0.w == 0.0f)) {
            std::cerr << "identity matrix col0 incorrect" << std::endl;
            return false;
        }
        if (!(m.col1.x == 0.0f && m.col1.y == 1.0f && m.col1.z == 0.0f && m.col1.w == 0.0f)) {
            std::cerr << "identity matrix col1 incorrect" << std::endl;
            return false;
        }
        if (!(m.col2.x == 0.0f && m.col2.y == 0.0f && m.col2.z == 1.0f && m.col2.w == 0.0f)) {
            std::cerr << "identity matrix col2 incorrect" << std::endl;
            return false;
        }
        if (!(m.col3.x == 0.0f && m.col3.y == 0.0f && m.col3.z == 0.0f && m.col3.w == 1.0f)) {
            std::cerr << "identity matrix col3 incorrect" << std::endl;
            return false;
        }
        return true;
        };
    test_component("Mat (constructors)", test_mat_constructors);

    // Mat operations
    auto test_mat_operations = []() -> bool {
        {
            constexpr Mat2f m(Vec2f(2.0f, 0.0f), Vec2f(0.0f, 3.0f));
            if (determinant(m) != 6.0f) {
                std::cerr << "Mat2f determinant failed (got " << determinant(m) << ")" << std::endl;
                return false;
            }
        }
        {
            constexpr Mat3f m(Vec3f(2.0f, 0.0f, 0.0f), Vec3f(0.0f, 3.0f, 0.0f), Vec3f(0.0f, 0.0f, 4.0f));
            if (determinant(m) != 24.0f) {
                std::cerr << "Mat3f determinant failed (got " << determinant(m) << ")" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Mat operations", test_mat_operations);

    // Quats
    auto test_quat_ops = []() -> bool {
        {
            constexpr Quatf q;
            if (!(q.x == 0.0f && q.y == 0.0f && q.z == 0.0f && q.w == 1.0f)) {
                std::cerr << "default quaternion constructor failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Quatf q(1.0f, 2.0f, 3.0f, 4.0f);
            constexpr Quatf cq = conjugate(q);
            if (!(cq.x == -1.0f && cq.y == -2.0f && cq.z == -3.0f && cq.w == 4.0f)) {
                std::cerr << "quaternion conjugate failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Quatf a(1.0f, 0.0f, 0.0f, 0.0f);
            constexpr Quatf b(1.0f, 0.0f, 0.0f, 0.0f);
            if (dot(a, b) != 1.0f) {
                std::cerr << "quaternion dot product failed (got " << dot(a, b) << ")" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Quat operations", test_quat_ops);

    // Color constructors and ops
    auto test_color_ops = []() -> bool {
        {
            constexpr Color3f c;
            if (!(c.r == 0.0f && c.g == 0.0f && c.b == 0.0f)) {
                std::cerr << "Color3f default constructor failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Color4f c;
            if (!(c.r == 0.0f && c.g == 0.0f && c.b == 0.0f && c.a == 1.0f)) {
                std::cerr << "Color4f default constructor failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Color3h c;
            if (!(c.r.data == 0 && c.g.data == 0 && c.b.data == 0)) {
                std::cerr << "Color3h default constructor failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Color4h c;
            if (!(c.r.data == 0 && c.g.data == 0 && c.b.data == 0 && c.a.data == 0x3C00)) {
                std::cerr << "Color4h default constructor failed (alpha=" << c.a.data << ")" << std::endl;
                return false;
            }
        }
        {
            constexpr Color3f a(0.5f, 0.5f, 0.5f);
            constexpr Color3f b(0.5f, 0.5f, 0.5f);
            constexpr Color3f sum = a + b;
            if (!(sum.r == 1.0f && sum.g == 1.0f && sum.b == 1.0f)) {
                std::cerr << "color addition failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Color4f c(1.0f, 1.0f, 1.0f, 1.0f);
            constexpr Color4f scaled = c * 0.5f;
            if (!(scaled.r == 0.5f && scaled.g == 0.5f && scaled.b == 0.5f && scaled.a == 0.5f)) {
                std::cerr << "color scaling failed" << std::endl;
                return false;
            }
        }
        {
            constexpr Color3h a(half{ 0x3C00 }, half{ 0x3C00 }, half{ 0x3C00 });
            constexpr Color3h b(half{ 0x3C00 }, half{ 0x3C00 }, half{ 0x3C00 });
            if (!(a == b)) {
                std::cerr << "half-precision color comparison failed" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Color operations", test_color_ops);

    // Box constructors
    auto test_box_constructors = []() -> bool {
        {
            constexpr Box3f empty;
            if (!empty.empty()) {
                std::cerr << "default box not empty" << std::endl;
                return false;
            }
        }
        {
            constexpr Vec3f p(1.0f, 2.0f, 3.0f);
            constexpr Box3f box(p);
            if (!(box.min.x == 1.0f && box.min.y == 2.0f && box.min.z == 3.0f)) {
                std::cerr << "box min point incorrect" << std::endl;
                return false;
            }
            if (!(box.max.x == 1.0f && box.max.y == 2.0f && box.max.z == 3.0f)) {
                std::cerr << "box max point incorrect" << std::endl;
                return false;
            }
        }
        return true;
        };
    test_component("Geom (constructors)", test_box_constructors);

    // Runtime tests with detailed diagnostics
    auto test_runtime = []() -> bool {
        bool success = true;

        // Vec3f length and normalize
        {
            Vec3f v(3.0f, 4.0f, 0.0f);
            if (!approx_equal(v.length(), 5.0f)) {
                std::cerr << "Vec3f length() failed (got " << v.length() << ")" << std::endl;
                success = false;
            }
            if (!approx_equal(v.length_sq(), 25.0f)) {
                std::cerr << "Vec3f length_sq() failed (got " << v.length_sq() << ")" << std::endl;
                success = false;
            }
            Vec3f n = v.normalized();
            if (!approx_equal(n.length(), 1.0f)) {
                std::cerr << "Vec3f normalized() length != 1.0" << std::endl;
                success = false;
            }
            if (!approx_equal(n.x, 0.6f) || !approx_equal(n.y, 0.8f)) {
                std::cerr << "Vec3f normalized() direction incorrect" << std::endl;
                success = false;
            }
            Vec3f zero;
            if (zero.try_normalize()) {
                std::cerr << "zero vector try_normalize() should fail" << std::endl;
                success = false;
            }
        }

        // Quaternion rotation
        {
            Quatf q = from_axis_angle(Vec3f(0.0f, 0.0f, 1.0f), pi_f * 0.5f);
            Vec3f rotated = rotate(q, Vec3f(1.0f, 0.0f, 0.0f));
            if (!approx_equal(rotated.x, 0.0f) || !approx_equal(rotated.y, 1.0f) || !approx_equal(rotated.z, 0.0f)) {
                std::cerr << "quaternion rotation failed (got [" << rotated.x << ", " << rotated.y << ", " << rotated.z << "])" << std::endl;
                success = false;
            }
        }

        // Transform
        {
            Mat4f m = translation(Vec3f(1.0f, 2.0f, 3.0f));
            Vec3f p(0.0f, 0.0f, 0.0f);
            Vec3f tp = transform_point(m, p);
            if (!approx_equal(tp.x, 1.0f) || !approx_equal(tp.y, 2.0f) || !approx_equal(tp.z, 3.0f)) {
                std::cerr << "transform_point failed (got [" << tp.x << ", " << tp.y << ", " << tp.z << "])" << std::endl;
                success = false;
            }

            Vec3f dir(1.0f, 0.0f, 0.0f);
            Vec3f td = transform_vector(m, dir);
            if (!approx_equal(td.x, 1.0f) || !approx_equal(td.y, 0.0f) || !approx_equal(td.z, 0.0f)) {
                std::cerr << "transform_vector failed (got [" << td.x << ", " << td.y << ", " << td.z << "])" << std::endl;
                success = false;
            }

            Mat4f rot_scale = from_trs(Vec3f(0.0f), Quatf(0.0f, 0.0f, 0.0f, 1.0f), Vec3f(2.0f, 2.0f, 2.0f));
            Vec3f normal(1.0f, 0.0f, 0.0f);
            Vec3f tn = transform_normal(rot_scale, normal);
            // After uniform scale (2,2,2), normal (1,0,0) becomes (0.5, 0, 0)
            if (!approx_equal(tn.x, 0.5f) || !approx_equal(tn.y, 0.0f) || !approx_equal(tn.z, 0.0f)) {
                std::cerr << "transform_normal direction incorrect (got [" << tn.x << ", " << tn.y << ", " << tn.z << "])" << std::endl;
                success = false;
            }
        }

        // Box operations
        {
            Box3f box(Vec3f(-1.0f, -1.0f, -1.0f), Vec3f(1.0f, 1.0f, 1.0f));
            if (box.empty()) {
                std::cerr << "valid box reported as empty" << std::endl;
                success = false;
            }
            if (!box.is_valid()) {
                std::cerr << "valid box reported as invalid" << std::endl;
                success = false;
            }
            if (!approx_equal(box.center().x, 0.0f)) {
                std::cerr << "box center incorrect (got " << box.center().x << ")" << std::endl;
                success = false;
            }
            if (!approx_equal(box.size().x, 2.0f)) {
                std::cerr << "box size incorrect (got " << box.size().x << ")" << std::endl;
                success = false;
            }
            box.extend(Vec3f(2.0f, 2.0f, 2.0f));
            if (!approx_equal(box.max.x, 2.0f)) {
                std::cerr << "box extend failed (max.x = " << box.max.x << ")" << std::endl;
                success = false;
            }
        }

        return success;
        };
    test_component("Runtime", test_runtime);

    // Final summary
    std::cout << "\nTest Basic Types result:" << std::endl;
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