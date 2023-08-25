#include "EnginePhysicsComponent.h"
#include "../Actor.h"

namespace jojo
{
	CLASS_DEFINITION(EnginePhysicsComponent)

	void jojo::EnginePhysicsComponent::Update(float dt)
	{
		m_owner->transform.position += m_velocity * dt;
		m_velocity += std::pow(1.0f - damping, dt);
	}

	void jojo::EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}

	void EnginePhysicsComponent::ApplyTorque(float torque)
	{
	}

	void EnginePhysicsComponent::Read(const json_t& value)
	{
		READ_DATA(value, damping);
	}
}

