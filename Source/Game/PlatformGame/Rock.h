#pragma once
#include "..\Engine\Framework\Actor.h"

namespace jojo
{
	class Rock : public jojo::Actor
	{
	public:
		CLASS_DECLARATION(Rock);

		virtual bool Initalize();
		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	protected:
		float speed = 0;
		float turnRate = 0;
	};
}