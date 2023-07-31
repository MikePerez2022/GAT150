#include "Actor.h"

namespace jojo
{
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1) 
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		m_transform.position += m_velocity * dt;
		m_velocity += std::pow(1.0f - m_dampening, dt);
	}
	void Actor::Draw(jojo::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}


}

