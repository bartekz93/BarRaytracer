#pragma once
#include"../../Raytracer/Scene.h"
#include"../../Raytracer/Objects.h"

namespace raytracerApp
{
	class Scene1 : public raytracer::Scene
	{
	private:
		raytracer::Material matMirrorRed;
		raytracer::Material matMirrorBlue;
		raytracer::Material matMirrorGreen;
		raytracer::Material matMirrorYellow;
		raytracer::Material matYellow;
		raytracer::Material matGreen;
		raytracer::Material matOrange;
		raytracer::Material matWhite;

		raytracer::Sphere s1;
		raytracer::Sphere s2;
		raytracer::Sphere s3;
		raytracer::Sphere s4;
		raytracer::Sphere s5;

		raytracer::Plane front;
		raytracer::Plane back;
		raytracer::Plane top;
		raytracer::Plane bottom;
		raytracer::Plane left;
		raytracer::Plane right;
	public:
		Scene1() {}

		void Scene1::Build() override;
	};
};