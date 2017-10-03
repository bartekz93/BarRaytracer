#pragma once
#include"SceneNode.h"

namespace raytracer
{
	class Camera : public SceneNode
	{
	public:
		float fovX;
		float width, height;
	};
}