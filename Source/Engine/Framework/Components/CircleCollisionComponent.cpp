#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace jojo
{
	CLASS_DEFINITION(CircleCollisionComponent)


	void jojo::CircleCollisionComponent::Update(float dt)
	{

	}

	bool jojo::CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
	{
		float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
		float radius = this->radius * collision->radius;

		return (distance <= radius);
	}

	void CircleCollisionComponent::Read(const json_t& value)
	{
		READ_DATA(value, radius);
	}

}

