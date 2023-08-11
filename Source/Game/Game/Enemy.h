#pragma once
#include "..\Engine\Framework\Actor.h"

class Enemy : public jojo::Actor
{
public:
	Enemy() = default;
	Enemy(float speed, float turnRate, const jojo::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;	
	}

	virtual bool Initalize();

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};