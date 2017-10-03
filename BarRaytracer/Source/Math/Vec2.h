#pragma once
#include<math.h>

namespace math
{
	struct Vec2
	{
		float x, y;

		Vec2() {}
		Vec2(float u, float v) : x(u), y(v) {}

		Vec2 operator+(const Vec2& v)	const { return Vec2(v.x + x, v.y + y);	}
		Vec2 operator-(const Vec2& v)	const { return Vec2(x - v.x, y - v.y);	}
		Vec2 operator*(float f)			const { return Vec2(x*f, y*f);			}
		Vec2 operator/(float f)			const { return Vec2(x / f, y / f);		}

		Vec2& operator+=(const Vec2& v) { x += v.x; y += v.y; return *this; }
		Vec2& operator-=(const Vec2& v) { x -= v.x; y -= v.y; return *this; }
		Vec2& operator*=(const Vec2& v) { x *= v.x; y *= v.y; return *this; }
		Vec2& operator/=(const Vec2& v) { x /= v.x; y /= v.y; return *this; }

		bool operator==(const Vec2& v) const { return (v.x == x && v.y == y); }
		bool operator!=(const Vec2& v) const { return (v.x != x || v.y != y); }

		float Length() const { return sqrt(pow(x, 2) + pow(y, 2)); }


		Vec2 yx() { return Vec2(y, x); }
	};
}