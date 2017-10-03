#include"SceneNode.h"

using namespace math;
using namespace raytracer;

void SceneNode::GetMatrix(Matrix4x4& mat)
{
	Math::ClampTo360(Yaw);
	Math::ClampTo360(Pitch);
	Math::ClampTo360(Roll);

	Forward = Vec3(0.0f, 0.0f, 1.0f);
	Up = Vec3(0.0f, 1.0f, 0.0f);
	Right = Vec3(1.0f, 0.0f, 0.0f);

	Matrix4x4 yaw, pitch, roll;
	yaw = Math::MatrixRotationAxis(Up, Yaw);
	pitch = Math::MatrixRotationAxis(Right, Pitch);
	roll = Math::MatrixRotationAxis(Forward, Roll);

	mat = yaw * pitch * roll;

	Forward = mat * Forward;
	Right = mat * Right;
	Up = mat * Up;

	mat.Set(3, 0, Pos.x);
	mat.Set(3, 1, Pos.y);
	mat.Set(3, 2, Pos.z);
}

void SceneNode::LookAt(Vec3 at) {
	
	
}