#pragma once
#include"Raytracer.h"

using namespace math;
using namespace framework;
using namespace renderer;
using namespace raytracer;

Raytracer::Raytracer() 
{
	currentScene = NULL;
	camera = NULL;
	light = NULL;
	renderer = NULL;
	manager = NULL;
	objects = NULL;
	objectsBuffer = NULL;
	settingsBuffer = NULL;
	quadVB = NULL;
	quadIB = NULL;
	VS = NULL;
	PS = NULL;
	compiledPS = NULL;
}


void Raytracer::Init(IRenderer* renderer, int w, int h) 
{
	this->renderer = renderer;
	this->manager = renderer->GetManager();
	screenW = w;
	screenH = h;

	renderer->SetViewport(0, 0, w, h);

	PrepareGeometry();
	PrepareShaders();
	PrepareSettingsBuffer();
}

void Raytracer::SetCamera(Camera& camera) 
{
	this->camera = &camera;

	settings.zNear = camera.width/2.0/tan(camera.fovX/2.0);
	settings.screenW = camera.width;
	settings.screenH = camera.height;
}


void Raytracer::SetScene(Scene& scene)
{

	auto spheres = scene.GetSpheres();
	auto planes = scene.GetPlanes();
	int numObjects = spheres.size() + planes.size();

	if (numObjects == 0) {
		Logger::Info("Scene has no objects.");
	}

	int objectIndex = 0;

	if (objects) {
		delete objects;
	}
	objects = new DTO::Object[numObjects];

	

	for each (auto plane in planes)
	{
		objects[objectIndex].type = 1;
		objects[objectIndex].pos = plane->Point;
		objects[objectIndex].norm = plane->Normal;
		objects[objectIndex].color = plane->Material->Color;
		objects[objectIndex].spec = plane->Material->Specular ? 1 : 0;
		objects[objectIndex].reflect = plane->Material->Reflect;
		objectIndex++;
	}

	for each (auto sphere in spheres)
	{
		objects[objectIndex].type = 0;
		objects[objectIndex].pos = sphere->Pos;
		objects[objectIndex].r = sphere->R;
		objects[objectIndex].color = sphere->Material->Color;
		objects[objectIndex].spec = sphere->Material->Specular ? 1 : 0;
		objects[objectIndex].reflect = sphere->Material->Reflect;
		objectIndex++;
	}

	settings.numObjects = numObjects;
	settings.light = scene.GetLight();
	currentScene = &scene;

	objectsBuffer = renderer->GetManager()->CreateStructuredBuffer(objects, sizeof(DTO::Object), numObjects);
	renderer->SetStructuredBuffer(objectsBuffer, 1);
}

void Raytracer::PrepareGeometry() 
{
	Vertex vertices[4] = 
	{ 
		{ Vec2(-1.0f, -1.0f) },
		{ Vec2(1.0f, -1.0f) },
		{ Vec2(1.0f, 1.0f) },
		{ Vec2(-1.0f, 1.0f) },
	};

	WORD indices[6] = { 0, 1, 2, 2, 3, 0 };

	quadVB = manager->CreateVertexBuffer(vertices, sizeof(Vertex) * 4);
	quadIB = manager->CreateIndexBuffer(indices, sizeof(WORD) * 6);

	renderer->SetVertexBuffer(quadVB, sizeof(Vertex), 0);
	renderer->SetIndexBuffer(quadIB);
}

void Raytracer::PrepareShaders() 
{
	VSLayout.Add(VertexElement("POSITION", VertexElement::VEC2, 8, 0));

	VS = manager->CreateVertexShader("Assets//shader.fx", VSLayout, "VS");
	compiledPS = manager->CompilePixelShader("Assets//shader.fx", "PSRaytracing");
	PS = manager->CreatePixelShader(*compiledPS);

	renderer->SetVertexLayout(&VSLayout);
	renderer->SetVertexShader(VS);
	renderer->SetPixelShader(PS);
}

void Raytracer::PrepareSettingsBuffer() 
{
	ZeroMemory(&settings, sizeof(settings));
	settings.screenH = screenW;
	settings.screenH = screenH;
	settings.numObjects = 0;
	settingsBuffer = manager->CreateConstantBuffer(&settings, sizeof(settings));

	renderer->SetConstantBuffer(settingsBuffer, 1);
}

void Raytracer::Render() 
{
	renderer->Render(0, 6);
}

void Raytracer::Update()
{
	camera->GetMatrix(settings.World);
	settings.light = currentScene->GetLight();
	manager->UpdateConstantBuffer(settingsBuffer, &settings);

}

void Raytracer::Release() {
	if (objects) {
		delete objects;
	}
}