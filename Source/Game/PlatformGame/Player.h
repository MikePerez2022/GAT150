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

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	protected:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;
		float maxspeed;

		PhysicsComponent* m_physicsComponent = nullptr;

		class SpriteAnim* m_spriteAnim = nullptr;
	};
}