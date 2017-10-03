#pragma once
#include"../App/Common.h"
#include"Scene.h"
#include"Camera.h"
#include"ShaderDTO.h"
#include"../Renderer/Interfaces/IRenderer.h"

namespace raytracer {

	struct Vertex {
		math::Vec2 Pos;
	};

	class Raytracer
	{
	private:
		int screenW;
		int screenH;

		renderer::IRenderer* renderer;
		renderer::IResourceManager* manager;
		
		DTO::Object* objects;
		DTO::Settings settings;

		renderer::StructuredBuffer* objectsBuffer;
		renderer::ConstantBuffer* settingsBuffer;
		renderer::VertexBuffer* quadVB;
		renderer::IndexBuffer* quadIB;
		renderer::VertexLayout VSLayout;
		renderer::VertexShader* VS;
		renderer::PixelShader* PS;
		renderer::CompiledPixelShader* compiledPS;

		Scene* currentScene;
		Camera* camera;
		math::Vec3* light;

		void PrepareGeometry();
		void PrepareShaders();
		void PrepareSettingsBuffer();

	public:
		Raytracer();

		void Init(renderer::IRenderer* renderer, int screenW, int screenH);
		void Render();
		void Update();
		void Release();

		void SetScene(Scene& scene);
		void SetCamera(Camera& camera);
	};
}




