#pragma once
#include "..\Engine\Framework\Actor.h"

namespace jojo
{
	class Enemy : public Actor
	{
	public:
		CLASS_DECLARATION(Enemy);

		virtual bool Initalize();
		void OnDestroy() override { m_destroyed = true; };
		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	protected:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float fireTimer = 0;

		//jojo::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
