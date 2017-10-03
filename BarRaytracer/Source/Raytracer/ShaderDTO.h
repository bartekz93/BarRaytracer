#pragma once
#include"../App/Common.h"
#include"../Math/Math.h"

// Here are shader data transfer objects. These structs describes format which in data is directly passed to shader.
// Fields in these structs have to be aligned to 16 bytes

namespace raytracer {
	namespace DTO {
		
		struct Settings
		{
			math::Matrix4x4 World;	// 4x16 camera transformation

			math::Vec3 light;		// 12
			int numObjects;			// 4
			
			float screenH;			// 4
			float zNear;			// 4
			float screenW;			// 4
			float alignation2;		// 4
		};

		struct Object
		{
			int type;				// 4
			math::Vec3 pos;			// 12

			float r;				// 4
			math::Vec3 norm;		// 12

			math::Vec3 color;		// 12
			float reflect;			// 4

			math::Vec3 specColor;	// 12
			int spec;				//	4

			/*
			int refract;
			int refractIndex*/
		};
	}
}
