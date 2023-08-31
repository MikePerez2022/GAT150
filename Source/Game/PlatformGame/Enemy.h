#pragma once
#include "..\Engine\Framework\Actor.h"

namespace jojo
{
	class Enemy : public jojo::Actor
	{
	public:
		CLASS_DECLARATION(Enemy);

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	protected:
		float speed = 0;
		float jump = 0;
		int GroundCount = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}