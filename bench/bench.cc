#include "lmath.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

struct Timer {
    using clock = std::chrono::high_resolution_clock;
    clock::time_point start;

    Timer() { reset(); }
    void reset() { start = clock::now(); }
    double elapsed_ms() const {
        auto end = clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};
 
float rand_f(std::mt19937& gen) {
    return static_cast<float>(gen() - gen.min()) / static_cast<float>(gen.max() - gen.min());
}

int main() {
    using namespace lmath;

    constexpr size_t N = 1'000'000; // iterations per test
    std::mt19937 rng(12345);

    std::cout << "Running lmath benchmark (" << N << " iterations per test)..\n\n";

    // Vecs
    {
        std::vector<Vec3f> a(N), b(N);
        for (size_t i = 0; i < N; ++i) {
            a[i] = Vec3f(rand_f(rng), rand_f(rng), rand_f(rng));
            b[i] = Vec3f(rand_f(rng), rand_f(rng), rand_f(rng));
        }

        volatile float sink = 0.0f;
        Timer t;
        for (size_t i = 0; i < N; ++i) {
            Vec3f c = a[i] + b[i];
            c = c * 2.0f;
            c = c.normalized();
            sink += c.x + c.y + c.z;
        }
        double ms = t.elapsed_ms();
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Vec3f arithmetic + normalize:\t" << ms << " ms";
        if (ms > 60.0) {
            std::cout << " (slow)";
        }
        else {
            std::cout << " OK";
        }
        std::cout << "\n";
        (void)sink;
    }

    // Mat4f * Vec4f
    {
        std::vector<Mat4f> mats(N);
        std::vector<Vec4f> vecs(N);
        for (size_t i = 0; i < N; ++i) {
            mats[i] = Mat4f(
                Vec4f(rand_f(rng), rand_f(rng), rand_f(rng), 0.0f),
                Vec4f(rand_f(rng), rand_f(rng), rand_f(rng), 0.0f),
                Vec4f(rand_f(rng), rand_f(rng), rand_f(rng), 0.0f),
                Vec4f(rand_f(rng), rand_f(rng), rand_f(rng), 1.0f)
            );
            vecs[i] = Vec4f(rand_f(rng), rand_f(rng), rand_f(rng), 1.0f);
        }

        volatile float sink = 0.0f;
        Timer t;
        for (size_t i = 0; i < N; ++i) {
            Vec4f r = mats[i] * vecs[i];
            sink += r.x + r.y + r.z + r.w;
        }
        double ms = t.elapsed_ms();
        std::cout << "Mat4f * Vec4f:\t\t\t" << ms << " ms";
        if (ms > 20.0) {
            std::cout << " (slow)";
        }
        else {
            std::cout << " OK";
        }
        std::cout << "\n";
        (void)sink;
    }

    // inverse(Mat4f)
    {
        const Vec3f axis = Vec3f(1.0f, 2.0f, 3.0f).normalized();

        std::vector<Mat4f> mats(N);
        for (size_t i = 0; i < N; ++i) {
            Vec3f t(rand_f(rng) * 10.0f, rand_f(rng) * 10.0f, rand_f(rng) * 10.0f);
            Vec3f s(0.5f + rand_f(rng), 0.5f + rand_f(rng), 0.5f + rand_f(rng));
            Quatf r = from_axis_angle(axis, rand_f(rng) * pi_f * 2.0f);
            mats[i] = from_trs(t, r, s);
        }

        volatile float sink = 0.0f;
        Timer t;
        for (size_t i = 0; i < N; ++i) {
            Mat4f inv_m = inverse(mats[i]);
            sink += inv_m.col0.x + inv_m.col0.y + inv_m.col0.z + inv_m.col0.w +
                inv_m.col1.x + inv_m.col1.y + inv_m.col1.z + inv_m.col1.w +
                inv_m.col2.x + inv_m.col2.y + inv_m.col2.z + inv_m.col2.w +
                inv_m.col3.x + inv_m.col3.y + inv_m.col3.z + inv_m.col3.w;
        }
        double ms = t.elapsed_ms();
        std::cout << "inverse(Mat4f):\t\t\t" << ms << " ms";
        if (ms > 100.0) {
            std::cout << " (slow)";
        }
        else {
            std::cout << " OK";
        }
        std::cout << "\n";
        (void)sink;
    }

    //  transform_normal
    {
        std::vector<Mat4f> mats(N);
        std::vector<Vec3f> normals(N);
        for (size_t i = 0; i < N; ++i) {
            Vec3f s(0.5f + rand_f(rng), 0.5f + rand_f(rng), 0.5f + rand_f(rng));
            mats[i] = scale(s);
            Vec3f n(rand_f(rng), rand_f(rng), rand_f(rng));
            normals[i] = n.normalized();
        }

        volatile float sink = 0.0f;
        Timer t;
        for (size_t i = 0; i < N; ++i) {
            Vec3f tn = transform_normal(mats[i], normals[i]);
            sink += tn.x + tn.y + tn.z;
        }
        double ms = t.elapsed_ms();
        std::cout << "transform_normal:\t\t" << ms << " ms";
        if (ms > 80.0) {
            std::cout << " (slow)";
        }
        else {
            std::cout << " OK";
        }
        std::cout << "\n";
        (void)sink;
    }

    std::cout << "\ndone.\n";
    return 0;
}