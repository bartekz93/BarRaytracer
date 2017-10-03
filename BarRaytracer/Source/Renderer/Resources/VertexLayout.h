#pragma once
#include "../../App/Common.h"
#include "../Interfaces/IResource.h"


namespace renderer
{

	struct VertexElement
	{
		enum DataType
		{
			VEC2, VEC3, VEC4
		};

		std::string SemanticName;
		DataType Type;
		uint Size;
		uint Offset;

		VertexElement(const std::string& semanticName, DataType type, uint size, uint offset) :
			SemanticName(semanticName), Type(type), Size(size), Offset(offset) {}
	};


	class VertexLayout : public IResource
	{
	private:
		std::vector<VertexElement> Elements;
	public:
		VertexLayout() : IResource() {}

		void Add(VertexElement el)
		{
			Elements.push_back(el);
		}
		const VertexElement& Get(uint i) const
		{
			if (i < Elements.size())
				return Elements[i];
		}
		uint GetSize() const { return Elements.size(); }

		void OnRelease() {}
	};
};