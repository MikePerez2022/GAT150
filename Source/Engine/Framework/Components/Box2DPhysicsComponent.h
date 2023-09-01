#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"


class b2Body;

namespace jojo
{
	class Box2DPhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(Box2DPhysicsComponent);

		bool Initialize() override;
		void OnDestroy() override;

		void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque);
		virtual void SetGravityScale(float scale);


		virtual void SetVelocity(const vec2& velocity) override;

		friend class Box2DCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;

		b2Body* m_body = nullptr;
	};
}