#pragma once
#include<math.h>

namespace math
{
	struct Vec4
	{
		float x, y, z, w;

		Vec4() {}
		Vec4(float u, float v, float t, float c) : x(u), y(v), z(t), w(c) {}

		Vec4 operator+(const Vec4& v) const { return Vec4(v.x + x, v.y + y, v.z + z, v.w + w); }
		Vec4 operator-(const Vec4& v) const { return Vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
		Vec4 operator*(float f) const { return Vec4(x*f, y*f, z*f, w*f); }
		Vec4 operator/(float f) const { return Vec4(x / f, y / f, z / f, w / f); }

		Vec4& operator+=(const Vec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		Vec4& operator-=(const Vec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		Vec4& operator*=(const Vec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		Vec4& operator/=(const Vec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

		bool operator==(const Vec4& v) const { return (v.x == x && v.y == y && v.z == z && v.w == w); }
		bool operator!=(const Vec4& v) const { return (v.x != x || v.y != y || v.z != z || v.w != w); }

		float Length() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)); }

		Vec4 wxyz() { return Vec4(w, x, y, z); }
	};
}