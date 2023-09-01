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

	protected:
		float speed = 0;
		float jump = 0;
		int Jumpcount = 0;
		float maxspeed;
		float jumpTime = 1.5;
		float jumpTimer = 0;

		Box2DPhysicsComponent* m_physicsComponent = nullptr;

		class SpriteAnim* m_spriteAnim = nullptr;
	};
}