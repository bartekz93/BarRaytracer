#pragma once
#include "../../App/Common.h"
#include "../Interfaces/IResource.h"

namespace renderer
{

	class VertexBuffer : public IResource
	{
	public:
		uint Size;

		void OnRelease() {}
	};

	class IndexBuffer : public IResource
	{
	public:
		void OnRelease() {}
	};

	class ConstantBuffer : public IResource {
		void OnRelease() {}
	};

	class StructuredBuffer : public IResource
	{
	public:
		void OnRelease() {}
	};

};