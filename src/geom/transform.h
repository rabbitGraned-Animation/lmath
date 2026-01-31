/*
 * lmath library
 * License: BSD 3-Clause License
 *
 * Copyright "rabbitGraned Animation"
 */

#pragma once

#include "core/constants.h"
#include "vec/vec3f.h"
#include "vec/vec4f.h"
#include "mat/mat4f.h"
#include "quat/quatf.h"

#include <cmath>
#include <cassert>

namespace lmath {
	constexpr Mat4f identity() noexcept {
		return Mat4f();
	}

	constexpr Mat4f translation(const Vec3f& v) noexcept {
		return Mat4f(
			Vec4f(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4f(v.x, v.y, v.z, 1.0f)
		);
	}

	constexpr Mat4f scale(const Vec3f& s) noexcept {
		return Mat4f(
			Vec4f(s.x, 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, s.y, 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, s.z, 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f)
		);
	}

	Mat4f rotation_axis_angle(const Vec3f& axis, float angle) noexcept {
		return to_mat4(from_axis_angle(axis, angle));
	}

	constexpr Mat4f from_trs(const Vec3f& t, const Quatf& r, const Vec3f& s) noexcept {
		Mat4f rot = to_mat4(r);
		Mat4f scl = scale(s);
		Mat4f trs = rot * scl;
		trs.col3 = Vec4f(t.x, t.y, t.z, 1.0f);
		return trs;
	}

	Mat4f perspective(float fovy, float aspect, float near, float far) noexcept {
		float tan_half_fovy = std::tan(fovy * 0.5f);
		return Mat4f(
			Vec4f(1.0f / (aspect * tan_half_fovy), 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, 1.0f / tan_half_fovy, 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, -(far + near) / (far - near), -1.0f),
			Vec4f(0.0f, 0.0f, -(2.0f * far * near) / (far - near), 0.0f)
		);
	}

	constexpr Mat4f ortho(float left, float right, float bottom, float top, float near, float far) noexcept {
		return Mat4f(
			Vec4f(2.0f / (right - left), 0.0f, 0.0f, 0.0f),
			Vec4f(0.0f, 2.0f / (top - bottom), 0.0f, 0.0f),
			Vec4f(0.0f, 0.0f, -2.0f / (far - near), 0.0f),
			Vec4f(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f)
		);
	}

	constexpr Vec3f transform_point(const Mat4f& m, const Vec3f& p) noexcept {
		Vec4f v = m * Vec4f(p.x, p.y, p.z, 1.0f);
		return Vec3f(v.x, v.y, v.z) / v.w;
	}

	constexpr Vec3f transform_vector(const Mat4f& m, const Vec3f& v) noexcept {
		Vec4f res = m * Vec4f(v.x, v.y, v.z, 0.0f);
		return Vec3f(res.x, res.y, res.z);
	}

	// Requires: upper 3x3 submatrix of m is invertible.
	constexpr Vec3f transform_normal(const Mat4f& m, const Vec3f& n) noexcept {
		Mat3f upper(
			Vec3f(m.col0.x, m.col0.y, m.col0.z),
			Vec3f(m.col1.x, m.col1.y, m.col1.z),
			Vec3f(m.col2.x, m.col2.y, m.col2.z)
		);
		return transpose(inverse(upper)) * n;
	}
}