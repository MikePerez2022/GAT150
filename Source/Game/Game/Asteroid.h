#pragma once
#include "..\Engine\Framework\Actor.h"
#include "Renderer/ModelManager.h"

class Asteroid : public jojo::Actor
{
public:
	Asteroid() = default;
	Asteroid(float speed, float turnRate, const jojo::Transform& transform) :
		Actor{ transform},
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
};