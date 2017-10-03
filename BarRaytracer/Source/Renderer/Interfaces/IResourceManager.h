#pragma once
#include<string>
#include<vector>
#include"IResource.h"
#include"../Resources/Shaders.h"
#include"../Resources/VertexLayout.h"

namespace renderer
{

	class IResourceManager
	{
	public:
		friend class IResource;

		vector<IResource*> Resources;

		virtual VertexShader* CreateVertexShader(const std::string& file, VertexLayout& inlayout, const std::string& funName) = 0;
		virtual CompiledPixelShader* CompilePixelShader(const std::string& file, const std::string& funName) = 0;
		virtual PixelShader* CreatePixelShader(const CompiledPixelShader& compiled) = 0;
		virtual VertexBuffer* CreateVertexBuffer(void* data, uint size) = 0;
		virtual IndexBuffer* CreateIndexBuffer(void* data, uint size) = 0;
		virtual ConstantBuffer* CreateConstantBuffer(void* data, uint size) = 0;
		virtual StructuredBuffer* CreateStructuredBuffer(void* data, uint stride, uint objects) = 0;

		virtual void UpdateConstantBuffer(ConstantBuffer* buffer, void* data) = 0;

		virtual void OnRelease() = 0;


		void Release()
		{
			OnRelease();

			for (int i = 0; i < Resources.size(); i++)
			{
				Resources[i]->Release();
				delete Resources[i];
			}
		}
		//virtual int Create
	};
}