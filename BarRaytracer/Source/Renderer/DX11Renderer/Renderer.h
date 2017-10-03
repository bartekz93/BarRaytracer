#pragma once
#include<D3D11.h>
#include"../../App/Common.h"
#include"../Interfaces/IRenderer.h"
#include"ResourceManager.h"

namespace dx11renderer
{
	using namespace renderer;

	class DX11Renderer : public IRenderer
	{
	private:
		const float ClearColor[4] = { 0.0f, 0.125f, 0.6f, 1.0f };

		VertexLayout* LastLayout;
		DX11ResourceManager* Manager;

		ID3D11Device* Dev;
		ID3D11DeviceContext* DevContext;
		IDXGISwapChain* SwapChain;
		ID3D11RenderTargetView* PrimaryRenderTarget;
		ID3D11RasterizerState* RasterizerState;

		bool CreateRT();
	public:
		bool Init(uint width, uint height, HWND hWnd, bool fullscreen = false)			override;
		void SetVertexBuffer(VertexBuffer* vb, uint stride, uint offset)				override;
		void SetIndexBuffer(IndexBuffer* ib)											override;
		void SetVertexLayout(VertexLayout* layout)										override;
		void SetConstantBuffer(ConstantBuffer* cb, uint slot)							override;
		void SetStructuredBuffer(StructuredBuffer* sb, uint slot)						override;
		void SetVertexShader(VertexShader* vs)											override;
		void SetPixelShader(PixelShader* pshader)										override;
		void SetViewport(float topLeftX, float topLeftY, float width, float height)		override;
		void Render(uint startIndex, uint indexCount)									override;
		void Release()																	override;

		DX11ResourceManager* GetManager() override {
			return Manager;
		}
	};
};