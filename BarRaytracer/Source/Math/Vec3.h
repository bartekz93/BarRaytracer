#pragma once
#include <math.h>

namespace math
{
	struct Vec3
	{
		float x, y, z;

		Vec3() {}
		Vec3(float u, float v, float t) : x(u), y(v), z(t) {}

		Vec3 operator+(const Vec3& v)	const	{	return Vec3(v.x + x, v.y + y, v.z + z);		}
		Vec3 operator-(const Vec3& v)	const	{	return Vec3(x - v.x, y - v.y, z - v.z);		}
		Vec3 operator*(float f)			const	{	return Vec3(x*f, y*f, z*f);					}
		Vec3 operator/(float f)			const	{	return Vec3(x / f, y / f, z / f);			}
		Vec3 operator-()				const	{	return Vec3(-x, -y, -z);					}

		Vec3& operator+=(const Vec3& v)			{ x += v.x; y += v.y; z += v.z; return *this;	}
		Vec3& operator-=(const Vec3& v)			{ x -= v.x; y -= v.y; z -= v.z; return *this;	}
		Vec3& operator*=(const Vec3& v)			{ x *= v.x; y *= v.y; z *= v.z; return *this;	}
		Vec3& operator/=(const Vec3& v)			{ x /= v.x; y /= v.y; z /= v.z; return *this;	}

		bool operator==(const Vec3& v)	const	{ return (v.x == x && v.y == y && v.z == z);	}
		bool operator!=(const Vec3& v)	const	{ return (v.x != x || v.y != y || v.z != z);	}

		float Length()					const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

		Vec3 xzy() { return Vec3(x, z, y); }
		Vec3 yxz() { return Vec3(y, x, z); }
		Vec3 yzx() { return Vec3(y, z, x); }
		Vec3 zxy() { return Vec3(z, x, y); }
		Vec3 zyx() { return Vec3(z, y, x); }
	};
}