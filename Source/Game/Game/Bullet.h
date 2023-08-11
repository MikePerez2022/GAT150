#pragma once
#include "..\Engine\Framework\Actor.h"


class Bullet : public jojo::Actor
{
public:
	Bullet() = default;
	Bullet(float speed, const jojo::Transform& transform) :
		Actor{ transform},
		m_speed{ speed }
	{}

	virtual bool Initalize();

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
};
