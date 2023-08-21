#pragma once
#include "..\Engine\Framework\Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public jojo::Actor
{
public:
	Player() = default;
	Player(float speed, float turnRate, const jojo::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate } 
	{
		lifespan = -1.0f;
	}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_coolDown = 1.5f;
	float m_coolDownTimer = 0;

	jojo::PhysicsComponent* m_physicsComponent = nullptr;
};