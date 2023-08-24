#pragma once
#include "CollisionComponent.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace jojo
{
	class Box2DCollisionComponent : public CollisionComponent
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(Box2DCollisionComponent);

		virtual bool Initialize() override;
		virtual void Update(float dt) override;

	public:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };

		// Inherited via CollisionComponent
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}