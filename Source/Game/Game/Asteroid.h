#pragma once
#include "..\Engine\Framework\Actor.h"

namespace jojo
{
	class Asteroid : public jojo::Actor
	{
	public:
		CLASS_DECLARATION(Asteroid);

		virtual bool Initalize();
		//void OnDestroy() override;
		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	protected:
		float speed = 0;
		float turnRate = 0;
	};
}

