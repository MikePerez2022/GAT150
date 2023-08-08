#include "EnginePhysicsComponent.h"
#include "../Actor.h"

void jojo::EnginePhysicsComponent::Update(float dt)
{
	m_owner->m_transform.position += m_velocity * dt;
	m_velocity += std::pow(1.0f - m_dampening, dt);
}

void jojo::EnginePhysicsComponent::ApplyForce(const vec2& force)
{
	m_velocity += force;
}
