#pragma once
#include "CollisionComponent.h"

namespace jojo
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		CLASS_DECLARATION(CircleCollisionComponent)		

		virtual void Update(float dt) override;

		virtual bool CheckCollision(CollisionComponent* collision) override;

	private:

	};
	
}