#pragma once
#include"../App/Common.h"
#include"../Math/Math.h"

namespace raytracer {

	//----------------------------------------------------------------------------------------

	class Material
	{
	public:
		math::Vec3 Color;
		bool Specular;
		float Reflect;
		//float Refract;

		Material() {}

		Material(math::Vec3 col, bool spec, float refl = 0) {
			Set(col, spec, refl);
		}

		void Set(math::Vec3 col, bool spec, float refl = 0) {
			Color = col;
			Specular = spec;
			Reflect = refl;
		}
	};

	//----------------------------------------------------------------------------------------

	class IObject
	{
	public:
		enum TYPE { SPHERE, PLANE };
		Material* Material;
		TYPE Type;

		IObject(TYPE type) : Type(type) {}
		virtual ~IObject() {}
	};
	

	//----------------------------------------------------------------------------------------

	class Sphere : public IObject
	{
	public:
		math::Vec3 Pos;
		float R;

		Sphere() : IObject(IObject::SPHERE) {};
		Sphere(math::Vec3 pos, float r) : IObject(IObject::SPHERE) {
			Set(pos, r);
		}

		void Set(math::Vec3 pos, float r) {
			Pos = pos;
			R = r;
		}
	};

	//----------------------------------------------------------------------------------------

	class Plane : public IObject
	{
	public:
		math::Vec3 Point;
		math::Vec3 Normal;

		Plane() : IObject(IObject::PLANE) {};
		Plane(math::Vec3 point, math::Vec3 norm) : IObject(IObject::PLANE) {
			Set(point, norm);
		}

		void Set(math::Vec3 point, math::Vec3 normal) {
			Normal = normal;
			Point = point;
		}

	};

	//----------------------------------------------------------------------------------------

	class Light
	{
	public:
		math::Vec3 Pos;

		Light() {}
		Light(const math::Vec3& pos) : Pos(pos) {}

		void Set(const math::Vec3& pos) {
			Pos = pos;
		}
	};
}