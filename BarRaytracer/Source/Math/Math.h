#pragma once
#include<math.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4x4.h"

namespace math
{
	
	class Math {
	public:
		static float Saturate(float f);
		static float Clamp(float min, float max, float f);
		static void ClampTo360(float& a);

		//-------------------------	Vec3
		
		static Vec3 Normalize(const Vec3& v);
		static void Normalize(const Vec3& v, Vec3& out);
		static float DotProduct(const Vec3& v, const Vec3& v2);
		static float GetCos(const Vec3& v, const Vec3& v2);
		static float GetAngleBetween(const Vec3& v, const Vec3& v2);
		static void ProjectAonB(const Vec3& a, const Vec3& b, Vec3& out);
		static void CrossProduct(const Vec3& v, const Vec3& v2, Vec3& out);
		static Vec3 Reflect(const Vec3& ray, const Vec3& normal);

		//-------------------------	Vec2

		static void Normalize(const Vec2& v, Vec2& out);
		static float DotProduct(const Vec2& v, const Vec2& v2);
		static float GetCos(const Vec2& v, const Vec2& v2);
		static void ProjectAonB(const Vec2& a, const Vec2& b, Vec2& out);

		//------------------------Matrix

		static Matrix4x4 MatrixLookAtLH(Vec3 eye, Vec3 at, Vec3 up);
		static Matrix4x4 MatrixPerspectiveFovLH(float angle, float aspect, float near, float far);
		static Matrix4x4 MatrixIdentity();
		static Matrix4x4 MatrixRotationX(float angle);
		static Matrix4x4 MatrixRotationY(float angle);
		static Matrix4x4 MatrixRotationZ(float angle);
		static Matrix4x4 MatrixRotationYawPitchRoll(float y, float p, float r);
		static Matrix4x4 MatrixRotationAxis(const Vec3& v, float a);
		static Matrix4x4 MatrixTranslation(float x, float y, float z);
		static Matrix4x4 MatrixTranspose(const Matrix4x4& m);
		static Matrix4x4 MatrixOrthoOffCenterLH(float minX, float maxX, float minY, float maxY, float zn, float zf);
	};

};