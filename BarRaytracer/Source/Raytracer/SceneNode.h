#pragma once
#include"../Math/Math.h"

namespace raytracer
{
	class SceneNode
	{
	protected:
		math::Vec3 Pos;

		math::Vec3 Right;
		math::Vec3 Up;
		math::Vec3 Forward;

		float Yaw, Pitch, Roll;

	public:
		const math::Vec3& GetPos() const { return Pos; }
		const math::Vec3& GetRight() const { return Right; }
		const math::Vec3& GetUp() const { return Up; }
		const math::Vec3& GetForward() const { return Forward; };
		float GetYaw() const { return Yaw; }
		float GetPitch() const { return Pitch; }
		float GetRoll() const { return Roll; }

		void MoveForward(float distance) { Pos += Forward * distance; }
		void MoveUp(float distance) { Pos += Up * distance; }
		void MoveRight(float distance) { Pos += Right * distance; }
		void Rotate(float yaw, float pitch, float roll) {
			Yaw += yaw;
			Pitch += pitch;
			Roll += roll;
		}
		void SetPos(math::Vec3 pos) {
			Pos = pos;
		}

		void LookAt(math::Vec3 at);
		void GetMatrix(math::Matrix4x4& mat);

		SceneNode() : Right(1.0f, 0.0f, 0.0f), Up(0.0f, 1.0f, 0.0f), Forward(0.0f, 0.0f, 1.0f), Yaw(0), Pitch(0), Roll(0) {}
	};
}