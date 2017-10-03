#include"RaytracerApp.h"

using namespace math;
using namespace framework;
using namespace raytracer;
using namespace raytracerApp;

void RaytracerApp::OnMouseMove(uint x, uint y, int relX, int relY, uint btn, uint key)
{
	if (btn == MK_LBUTTON) {
		camera.Rotate(relX*0.01, relY*0.01, 0);
	}
}

void RaytracerApp::OnKeyDown(uint key)
{
	static float m = 1.0f;
	if (key == VK_LEFT) camera.MoveRight(-m);
	if (key == VK_RIGHT) camera.MoveRight(m);
	if (key == VK_DOWN) camera.MoveForward(-m);
	if (key == VK_UP) camera.MoveForward(m);
}

void RaytracerApp::OnChar(char c)
{
}

void RaytracerApp::OnInit() 
{
	AddInputListener(*this);

	renderer.Init(width, height, hWnd, false);
	raytracer.Init(&renderer, width, height);

	scene.Build();
	camera.SetPos(Vec3(0, 0, -20));

	camera.fovX = 3.1415 / 2;
	camera.width = width;
	camera.height = height;

	raytracer.SetScene(scene);
	raytracer.SetCamera(camera);
}

void RaytracerApp::OnUpdate() 
{
	raytracer.Update();
}

void RaytracerApp::OnRender() 
{
	raytracer.Render();
}

void RaytracerApp::OnRelease() 
{
	renderer.Release();
	raytracer.Release();
}