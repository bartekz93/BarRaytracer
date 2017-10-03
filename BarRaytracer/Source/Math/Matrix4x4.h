#pragma once
#include<math.h>
#include"Vec3.h"
#include"Vec4.h"

namespace math
{
	struct Matrix4x4
	{
		float m[16];

		float Get(int x, int y) const { return m[4 * y + x]; }
		void Set(int x, int y, float f) { m[4 * y + x] = f; }

		Matrix4x4 operator*(const Matrix4x4& mat) const
		{
			Matrix4x4 out;
			for (int i = 0; i<4; i++)
			{
				for (int k = 0; k<4; k++)
				{
					float sum = 0;
					for (int j = 0; j<4; j++)
					{
						sum += Get(j, i) * mat.Get(k, j);
					}
					out.Set(k, i, sum);
				}
			}
			return out;
		}
		Matrix4x4 operator*(float f) const
		{
			Matrix4x4 mt;
			for (int i = 0; i<16; i++) mt.m[i] = m[i] * f;
			return mt;
		}
		Matrix4x4 operator/(float f) const
		{
			Matrix4x4 mt;
			for (int i = 0; i<16; i++) mt.m[i] = m[i] / f;
			return mt;
		}
		Matrix4x4 operator+(float f) const
		{
			Matrix4x4 mt;
			for (int i = 0; i<16; i++) mt.m[i] = m[i] + f;
			return mt;
		}
		Matrix4x4 operator-(float f) const
		{
			Matrix4x4 mt;
			for (int i = 0; i<16; i++) mt.m[i] = m[i] - f;
			return mt;
		}
		Matrix4x4 operator+(const Matrix4x4 mat) const
		{
			Matrix4x4 mt;
			for (int i = 0; i<16; i++) mt.m[i] = m[i] + mat.m[i];
			return mt;
		}
		Matrix4x4 operator-(Matrix4x4 mat) const
		{
			Matrix4x4 mt;
			for (int i = 0; i<16; i++) mt.m[i] = m[i] - mat.m[i];
			return mt;
		}

		Matrix4x4& operator*=(float f)
		{
			for (int i = 0; i<16; i++) m[i] = m[i] * f;
			return *this;
		}
		Matrix4x4& operator/=(float f)
		{

			for (int i = 0; i<16; i++) m[i] = m[i] / f;
			return *this;
		}
		Matrix4x4& operator+=(float f)
		{

			for (int i = 0; i<16; i++) m[i] = m[i] + f;
			return *this;
		}
		Matrix4x4& operator-=(float f)
		{

			for (int i = 0; i<16; i++) m[i] = m[i] - f;
			return *this;
		}
		Matrix4x4& operator+(Matrix4x4 mat)
		{

			for (int i = 0; i<16; i++) m[i] = m[i] + mat.m[i];
			return *this;
		}
		Matrix4x4& operator-(Matrix4x4 mat)
		{

			for (int i = 0; i<16; i++) m[i] = m[i] - mat.m[i];
			return *this;
		}

		Vec3 operator*(const Vec3& v)
		{
			return Vec3(v.x*m[0] + v.y*m[1] + v.z*m[2] + m[3],
				v.x*m[4] + v.y*m[5] + v.z*m[6] + m[7],
				v.x*m[8] + v.y*m[9] + v.z*m[10] + m[11]);
		}

		/*
		Vec4 operator*(const Vec3& v)
		{
		return Vec4(v.x*m[0] + v.y*m[1] + v.z*m[2] + m[3],
		v.x*m[4] + v.y*m[5] + v.z*m[6] + m[7],
		v.x*m[8] + v.y*m[9] + v.z*m[10] + m[11],
		v.x*m[12] + v.y*m[13] + v.z*m[14] + m[15]);
		}*/

		Vec4 operator*(const Vec4& v)
		{
			return Vec4(v.x*m[0] + v.y*m[4] + v.z*m[8] + v.w*m[12],
						v.x*m[1] + v.y*m[5] + v.z*m[9] + v.w*m[13],
						v.x*m[2] + v.y*m[6] + v.z*m[10] + v.w*m[14],
						v.x*m[3] + v.y*m[7] + v.z*m[11] + v.w*m[15]);
		}
	};
}