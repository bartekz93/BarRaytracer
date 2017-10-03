#include "Scene1.h"

using namespace math;
using namespace raytracer;
using namespace raytracerApp;

void Scene1::Build()
{
	matMirrorRed.Set(Vec3(1, 0, 0), true, 0.4);
	matMirrorGreen.Set(Vec3(0, 1, 0), true, 0.4);
	matMirrorYellow.Set(Vec3(1, 1, 0), true, 0.4);
	matMirrorBlue.Set(Vec3(0, 0, 1), true, 0.4);
	matOrange.Set(Vec3(1, 0.5, 0), false, 0);
	matGreen.Set(Vec3(0, 1, 0), false, 0);
	matYellow.Set(Vec3(1, 1, 0), false, 0);
	matWhite.Set(Vec3(1, 1, 1), false, 0);

	s1.Set(Vec3(5, 0, 5), 5);
	s2.Set(Vec3(-5, 0, -5), 5);
	s3.Set(Vec3(-5, 0, 5), 5);
	s4.Set(Vec3(5, 0, -5), 5);
	s5.Set(Vec3(0, 7, 0), 5);

	bottom.Set(Vec3(0.0f, -4.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	front.Set(Vec3(0.0f, 0.0f, 30.0f), Vec3(0.0f, 0.0f, -1.0f));
	back.Set(Vec3(0.0f, 0.0f, -30.0f), Vec3(0.0f, 0.0f, 1.0f));
	left.Set(Vec3(-30.0f, 0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	right.Set(Vec3(30.0f, 0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	top.Set(Vec3(0.0f, 30.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f));


	bottom.Material = &matWhite;
	top.Material = &matOrange;
	front.Material = &matMirrorRed;
	back.Material = &matYellow;
	left.Material = &matGreen;
	right.Material = &matMirrorBlue;

	s1.Material = &matMirrorYellow;
	s2.Material = &matMirrorGreen;
	s3.Material = &matMirrorBlue;
	s4.Material = &matMirrorYellow;
	s5.Material = &matMirrorRed;

	spheres.push_back(&s1);
	spheres.push_back(&s2);
	spheres.push_back(&s3);
	spheres.push_back(&s4);
	spheres.push_back(&s5);
	planes.push_back(&bottom);
	planes.push_back(&top);
	planes.push_back(&left);
	planes.push_back(&right);
	planes.push_back(&front);
	planes.push_back(&back);

	light = Vec3(-20, 20, 0);
}