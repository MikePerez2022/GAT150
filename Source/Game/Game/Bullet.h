#pragma once
#include "..\Engine\Framework\Actor.h"

namespace jojo
{
	class Bullet : public Actor
	{
	public:
		CLASS_DECLARATION(Bullet)

		virtual bool Initalize();

		void Update(float dt) override;
		void OnCollision(Actor* other);

	protected:
		float speed = 0;
	};
}