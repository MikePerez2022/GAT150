#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"

namespace jojo
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;

		virtual void SetVelocity(const vec2& velocity) { m_velocity = velocity; }

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float damping = 0.0f;
	};
}