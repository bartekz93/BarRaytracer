#pragma once
#include "../App/Common.h"
#include "../App/App.h"
#include "../Renderer/DX11Renderer/Renderer.h"
#include "../Raytracer/Raytracer.h"
#include "../Raytracer/Camera.h"
#include "./Scenes/Scene1.h"


namespace raytracerApp
{

	class RaytracerApp : public framework::App, public framework::IInputListener {

	public:
		RaytracerApp() {}

		void OnMouseMove(uint x, uint y, int relX, int relY, uint btn, uint key) override;
		void OnKeyDown(uint key) override;
		void OnChar(char c) override;
	protected:
		dx11renderer::DX11Renderer renderer;
		raytracer::Raytracer raytracer;

		raytracer::Camera camera;
		Scene1 scene;

		void OnInit() override;
		void OnUpdate() override;
		void OnRender() override;
		void OnRelease() override;
	};
};