#include "Bullet.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

namespace jojo
{
	CLASS_DEFINITION(Bullet);

	bool Bullet::Initalize()
	{
		Actor::Initialize();

		auto collisionComponent = GetComponent<jojo::CollisionComponent>();

		if (collisionComponent)
		{
			auto renderComponent = GetComponent<jojo::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<jojo::RenderComponent>()->GetRadius() / scale;
			}
		}

		return true;
	}

	void Bullet::Update(float dt)
	{
		Actor::Update(dt);

		jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(transform.rotation);
		transform.position += forward * speed * jojo::g_time.GetDeltaTime();
		transform.position.x = jojo::Wrap(transform.position.x, (float)jojo::g_renderer.GetWidth());

	}


	void Bullet::OnCollision(Actor* other)
	{
		if (other->tag != tag)
		{
			m_destroyed = true;
		}
	}

	void Bullet::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}




