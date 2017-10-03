#pragma once
#include<D3D11.h>
#include"../../App/Common.h"
#include"../Resources/Shaders.h"
#include"../Resources/Buffers.h"
#include"../Resources/VertexLayout.h"
#include"../Interfaces/IResourceManager.h"


namespace dx11renderer
{
	using namespace renderer;

	class DX11ResourceManager : public IResourceManager
	{
	private:
		vector<ID3D11Buffer*> VertexBuffers;
		vector<ID3D11Buffer*> IndexBuffers;
		vector<ID3D11Buffer*> StructuredBuffers;
		vector<ID3D11Buffer*> ConstantBuffers;
		vector<ID3D11InputLayout*> InputLayouts;
		vector<ID3D11VertexShader*> VertexShaders;
		vector<ID3D11PixelShader*> PixelShaders;
		vector<ID3D11ShaderResourceView*> StructuredBuffersViews;

		ID3D11Device* Dev;
		ID3D11DeviceContext* DevContext;


		bool CreateBufferShaderResourceView(ID3D11Buffer* pBuffer);
	public:
		DX11ResourceManager(ID3D11Device* dev, ID3D11DeviceContext* context);

		void OnRelease() override;

		CompiledPixelShader* CompilePixelShader(const string& file, const string& funName) override;
		VertexShader* CreateVertexShader(const string& file, VertexLayout& inlayout, const string& funName) override;
		PixelShader* CreatePixelShader(const CompiledPixelShader& compiled) override;
		VertexBuffer* CreateVertexBuffer(void* data, uint size) override;
		IndexBuffer* CreateIndexBuffer(void* data, uint size) override;
		ConstantBuffer* CreateConstantBuffer(void* data, uint size) override;
		StructuredBuffer* CreateStructuredBuffer(void* data, uint stride, uint objects) override;

		void UpdateConstantBuffer(ConstantBuffer* buffer, void* data) override;

		ID3D11Buffer* GetDXVertexBuffer(VertexBuffer* vb);
		ID3D11Buffer* GetDXIndexBuffer(IndexBuffer* ib);
		ID3D11Buffer* GetDXStructuredBuffer(StructuredBuffer* sb);
		ID3D11Buffer* GetDXConstantBuffer(ConstantBuffer* cb);
		ID3D11InputLayout* GetDXInputLayout(VertexLayout* inlayout);
		ID3D11VertexShader* GetDXVertexShader(VertexShader* vs);
		ID3D11PixelShader* GetDXPixelShader(PixelShader* ps);
		ID3D11ShaderResourceView* GetDXStructuredBuffersView(StructuredBuffer* sb);
	};
};