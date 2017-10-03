#pragma once
#include<string>

typedef unsigned int uint;

namespace renderer
{

	class IResource
	{
	protected:
		friend class IResourceManager;
		int id;
		uint Counter;
	public:
		IResource() {
			id = -1;
		}

		int GetId() const {
			return id;
		}

		void SetId(uint _id) {
			id = _id;
		}

		virtual const std::string& GetType() const {
			return "Unknown resource";
		}

		void Release() {
			Counter--; OnRelease();
		}

		virtual void OnRelease() = 0;
	};
}