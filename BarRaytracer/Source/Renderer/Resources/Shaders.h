#pragma once
#include "../../App/Common.h"
#include "../Interfaces/IResource.h"
#include "VertexLayout.h"

namespace renderer
{

	class VertexShader : public IResource
	{
	public:
		VertexLayout* InputLayout;
		void OnRelease() {}
	};

	class PixelShader : public IResource
	{
	public:
		void OnRelease() {}
	};


	class CompiledPixelShader : public IResource
	{
	public:
		char* Data;
		uint Size;

		void OnRelease();
		bool SaveToFile(const string& file);
		bool LoadFromFile(const string& file);
	};
};