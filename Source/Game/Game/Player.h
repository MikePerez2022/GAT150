#pragma once
#include "..\Engine\Framework\Actor.h"
namespace jojo
{
	class Player : public jojo::Actor
	{
	public:
		CLASS_DECLARATION(Player);

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(Actor* other) override;
		//void OnDestroy() override;

	protected:
		float speed = 0;
		float turnRate = 0;

		float m_coolDown = 1.5f;
		float m_coolDownTimer = 0;

		//jojo::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
