/*
 * lmath library
 * License: BSD 3-Clause License
 *
 * Copyright "rabbitGraned Animation"
 */

#pragma once

#include "core/constants.h"
#include "vec/vec3d.h"
#include "mat/mat3d.h"

#include <cmath>
#include <cassert>

namespace lmath {
	struct Quatd {
		double x;
		double y;
		double z;
		double w;

		constexpr Quatd() noexcept : x(0.0), y(0.0), z(0.0), w(1.0) {}
		constexpr Quatd(double vx, double vy, double vz, double vw) noexcept
			: x(vx), y(vy), z(vz), w(vw) {
		}
		constexpr explicit Quatd(const Vec3d& v, double s) noexcept
			: x(v.x), y(v.y), z(v.z), w(s) {
		}

		constexpr double length_sq() const noexcept {
			return x * x + y * y + z * z + w * w;
		}

		double length() const noexcept {
			return std::sqrt(length_sq());
		}

		Quatd normalized() const noexcept;
		Quatd& normalize() noexcept;
		bool try_normalize(double eps = epsilon_d) noexcept;

		constexpr Quatd& operator*=(double s) noexcept {
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		constexpr Quatd& operator/=(double s) noexcept {
			double inv = 1.0 / s;
			x *= inv;
			y *= inv;
			z *= inv;
			w *= inv;
			return *this;
		}
	};

	constexpr Quatd operator+(const Quatd& a, const Quatd& b) noexcept;
	constexpr Quatd operator-(const Quatd& a, const Quatd& b) noexcept;
	constexpr Quatd operator*(const Quatd& a, const Quatd& b) noexcept;
	constexpr Quatd operator*(const Quatd& q, double s) noexcept;
	constexpr Quatd operator*(double s, const Quatd& q) noexcept;
	constexpr Quatd operator/(const Quatd& q, double s) noexcept;
	constexpr Quatd operator-(const Quatd& q) noexcept;

	inline Quatd Quatd::normalized() const noexcept {
		double len = length();
		return (*this) / len;
	}

	inline Quatd& Quatd::normalize() noexcept {
		double len = length();
		return (*this) /= len;
	}

	inline bool Quatd::try_normalize(double eps) noexcept {
		double len_sq = length_sq();
		if (len_sq <= eps * eps) {
			return false;
		}
		double inv_len = 1.0 / std::sqrt(len_sq);
		x *= inv_len;
		y *= inv_len;
		z *= inv_len;
		w *= inv_len;
		return true;
	}

	constexpr Quatd operator+(const Quatd& a, const Quatd& b) noexcept {
		return Quatd(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	constexpr Quatd operator-(const Quatd& a, const Quatd& b) noexcept {
		return Quatd(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	constexpr Quatd operator*(const Quatd& a, const Quatd& b) noexcept {
		return Quatd(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
	}

	constexpr Quatd operator*(const Quatd& q, double s) noexcept {
		return Quatd(q.x * s, q.y * s, q.z * s, q.w * s);
	}

	constexpr Quatd operator*(double s, const Quatd& q) noexcept {
		return q * s;
	}

	constexpr Quatd operator/(const Quatd& q, double s) noexcept {
		double inv = 1.0 / s;
		return Quatd(q.x * inv, q.y * inv, q.z * inv, q.w * inv);
	}

	constexpr Quatd operator-(const Quatd& q) noexcept {
		return Quatd(-q.x, -q.y, -q.z, -q.w);
	}

	constexpr Quatd conjugate(const Quatd& q) noexcept {
		return Quatd(-q.x, -q.y, -q.z, q.w);
	}

	constexpr double dot(const Quatd& a, const Quatd& b) noexcept {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	constexpr Vec3d rotate(const Quatd& q, const Vec3d& v) noexcept {
		Vec3d t = cross(Vec3d(q.x, q.y, q.z), v) * 2.0;
		return v + t * q.w + cross(Vec3d(q.x, q.y, q.z), t);
	}

	constexpr Mat3d to_mat3(const Quatd& q) noexcept {
		double xx = q.x * q.x;
		double yy = q.y * q.y;
		double zz = q.z * q.z;
		double xy = q.x * q.y;
		double xz = q.x * q.z;
		double yz = q.y * q.z;
		double xw = q.x * q.w;
		double yw = q.y * q.w;
		double zw = q.z * q.w;
		return Mat3d(
			Vec3d(1.0 - 2.0 * (yy + zz), 2.0 * (xy - zw), 2.0 * (xz + yw)),
			Vec3d(2.0 * (xy + zw), 1.0 - 2.0 * (xx + zz), 2.0 * (yz - xw)),
			Vec3d(2.0 * (xz - yw), 2.0 * (yz + xw), 1.0 - 2.0 * (xx + yy)));
	}

	constexpr Mat4d to_mat4(const Quatd& q) noexcept {
		Mat3d m = to_mat3(q);
		return Mat4d(
			Vec4d(m.col0.x, m.col0.y, m.col0.z, 0.0),
			Vec4d(m.col1.x, m.col1.y, m.col1.z, 0.0),
			Vec4d(m.col2.x, m.col2.y, m.col2.z, 0.0),
			Vec4d(0.0, 0.0, 0.0, 1.0));
	}

	Quatd from_axis_angle(const Vec3d& axis, double angle) noexcept {
		double half_angle = angle * 0.5;
		double s = std::sin(half_angle);
		double c = std::cos(half_angle);
		Vec3d unit_axis = axis.normalized();
		return Quatd(unit_axis.x * s, unit_axis.y * s, unit_axis.z * s, c);
	}

	constexpr bool operator==(const Quatd& a, const Quatd& b) noexcept {
		return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
	}

	constexpr bool operator!=(const Quatd& a, const Quatd& b) noexcept {
		return !(a == b);
	}

	template <>
	struct is_quat<Quatd> : std::true_type {};
}  // namespace lmath