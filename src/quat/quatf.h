/*
 * lmath library
 * License: BSD 3-Clause License
 *
 * Copyright "rabbitGraned Animation"
 */

#pragma once

#include "core/constants.h"
#include "vec/vec3f.h"
#include "mat/mat3f.h"

#include <cmath>
#include <cassert>

namespace lmath {
	struct Quatf {
		float x;
		float y;
		float z;
		float w;

		constexpr Quatf() noexcept : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		constexpr Quatf(float vx, float vy, float vz, float vw) noexcept
			: x(vx), y(vy), z(vz), w(vw) {
		}
		constexpr explicit Quatf(const Vec3f& v, float s) noexcept
			: x(v.x), y(v.y), z(v.z), w(s) {
		}

		constexpr float length_sq() const noexcept {
			return x * x + y * y + z * z + w * w;
		}

		float length() const noexcept {
			return std::sqrt(length_sq());
		}

		Quatf normalized() const noexcept;
		Quatf& normalize() noexcept;
		bool try_normalize(float eps = epsilon_f) noexcept;

		constexpr Quatf& operator*=(float s) noexcept {
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		constexpr Quatf& operator/=(float s) noexcept {
			float inv = 1.0f / s;
			x *= inv;
			y *= inv;
			z *= inv;
			w *= inv;
			return *this;
		}
	};

	constexpr Quatf operator+(const Quatf& a, const Quatf& b) noexcept;
	constexpr Quatf operator-(const Quatf& a, const Quatf& b) noexcept;
	constexpr Quatf operator*(const Quatf& a, const Quatf& b) noexcept;
	constexpr Quatf operator*(const Quatf& q, float s) noexcept;
	constexpr Quatf operator*(float s, const Quatf& q) noexcept;
	constexpr Quatf operator/(const Quatf& q, float s) noexcept;
	constexpr Quatf operator-(const Quatf& q) noexcept;

	inline Quatf Quatf::normalized() const noexcept {
		float len = length();
		return (*this) / len;
	}

	inline Quatf& Quatf::normalize() noexcept {
		float len = length();
		return (*this) /= len;
	}

	inline bool Quatf::try_normalize(float eps) noexcept {
		float len_sq = length_sq();
		if (len_sq <= eps * eps) {
			return false;
		}
		float inv_len = 1.0f / std::sqrt(len_sq);
		x *= inv_len;
		y *= inv_len;
		z *= inv_len;
		w *= inv_len;
		return true;
	}

	constexpr Quatf operator+(const Quatf& a, const Quatf& b) noexcept {
		return Quatf(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	constexpr Quatf operator-(const Quatf& a, const Quatf& b) noexcept {
		return Quatf(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	constexpr Quatf operator*(const Quatf& a, const Quatf& b) noexcept {
		return Quatf(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
	}

	constexpr Quatf operator*(const Quatf& q, float s) noexcept {
		return Quatf(q.x * s, q.y * s, q.z * s, q.w * s);
	}

	constexpr Quatf operator*(float s, const Quatf& q) noexcept {
		return q * s;
	}

	constexpr Quatf operator/(const Quatf& q, float s) noexcept {
		float inv = 1.0f / s;
		return Quatf(q.x * inv, q.y * inv, q.z * inv, q.w * inv);
	}

	constexpr Quatf operator-(const Quatf& q) noexcept {
		return Quatf(-q.x, -q.y, -q.z, -q.w);
	}

	constexpr Quatf conjugate(const Quatf& q) noexcept {
		return Quatf(-q.x, -q.y, -q.z, q.w);
	}

	constexpr float dot(const Quatf& a, const Quatf& b) noexcept {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	constexpr Vec3f rotate(const Quatf& q, const Vec3f& v) noexcept {
		Vec3f t = cross(Vec3f(q.x, q.y, q.z), v) * 2.0f;
		return v + t * q.w + cross(Vec3f(q.x, q.y, q.z), t);
	}

	constexpr Mat3f to_mat3(const Quatf& q) noexcept {
		float xx = q.x * q.x;
		float yy = q.y * q.y;
		float zz = q.z * q.z;
		float xy = q.x * q.y;
		float xz = q.x * q.z;
		float yz = q.y * q.z;
		float xw = q.x * q.w;
		float yw = q.y * q.w;
		float zw = q.z * q.w;
		return Mat3f(
			Vec3f(1.0f - 2.0f * (yy + zz), 2.0f * (xy - zw), 2.0f * (xz + yw)),
			Vec3f(2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xw)),
			Vec3f(2.0f * (xz - yw), 2.0f * (yz + xw), 1.0f - 2.0f * (xx + yy)));
	}

	constexpr Mat4f to_mat4(const Quatf& q) noexcept {
		Mat3f m = to_mat3(q);
		return Mat4f(
			Vec4f(m.col0.x, m.col0.y, m.col0.z, 0.0f),
			Vec4f(m.col1.x, m.col1.y, m.col1.z, 0.0f),
			Vec4f(m.col2.x, m.col2.y, m.col2.z, 0.0f),
			Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
	}

	Quatf from_axis_angle(const Vec3f& axis, float angle) noexcept {
		float half_angle = angle * 0.5f;
		float s = std::sin(half_angle);
		float c = std::cos(half_angle);
		Vec3f unit_axis = axis.normalized();
		return Quatf(unit_axis.x * s, unit_axis.y * s, unit_axis.z * s, c);
	}

	constexpr bool operator==(const Quatf& a, const Quatf& b) noexcept {
		return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
	}

	constexpr bool operator!=(const Quatf& a, const Quatf& b) noexcept {
		return !(a == b);
	}

	template <>
	struct is_quat<Quatf> : std::true_type {};
}  // namespace lmath