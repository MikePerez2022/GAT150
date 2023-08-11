#include "Bullet.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

bool Bullet::Initalize()
{
	Actor::Initialize();

	auto collisionComponent = GetComponent<jojo::CollisionComponent>();

	if (collisionComponent)
	{
		auto renderComponent = GetComponent<jojo::RenderComponent>();
		if (renderComponent)
		{
			float scale = m_transform.scale;
			collisionComponent->m_radius = GetComponent<jojo::RenderComponent>()->GetRadius() / scale;
		}
	}

	return true;
}

void Bullet::Update(float dt)
{
	Actor::Update(dt);

	jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * jojo::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());

}

void Bullet::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag)
	{
		m_destroyed = true;
	}
}
