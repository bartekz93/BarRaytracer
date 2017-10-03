#pragma once
#include"../Resources/Buffers.h"
#include"../Resources/Shaders.h"
#include"../Resources/VertexLayout.h"
#include"IResourceManager.h"

typedef unsigned int uint;

namespace renderer
{

	class IRenderer
	{
	public:
		virtual bool Init(uint width, uint height, HWND hWnd, bool fullscreen = false) = 0;
		virtual void SetVertexBuffer(VertexBuffer* vb, uint stride, uint offset) = 0;
		virtual void SetIndexBuffer(IndexBuffer* ib) = 0;
		virtual void SetConstantBuffer(ConstantBuffer* cb, uint slot) = 0;
		virtual void SetStructuredBuffer(StructuredBuffer* sb, uint slot) = 0;
		virtual void SetVertexShader(VertexShader* vs) = 0;
		virtual void SetVertexLayout(VertexLayout* layout) = 0;
		virtual void SetPixelShader(PixelShader* ps) = 0;
		virtual void SetViewport(float topLeftX, float topLeftY, float width, float height) = 0;
		virtual void Render(uint startIndex, uint indexCount) = 0;

		virtual void Release() = 0;

		virtual IResourceManager* GetManager() = 0;
	};
};