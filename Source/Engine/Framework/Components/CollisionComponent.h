#pragma once
#include "Component.h"

namespace jojo
{

	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision) = 0 { return true; };

	public:
		float radius = 0;

	};

}