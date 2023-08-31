#include "Bullet.h"
#include "Renderer/Renderer.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Components/PhysicsComponent.h"

namespace jojo
{
	CLASS_DEFINITION(Bullet);

	bool Bullet::Initalize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<jojo::PhysicsComponent>();

		auto collisionComponent = GetComponent<jojo::CollisionComponent>();

		if (collisionComponent)
		{

		}

		return true;
	}

	void Bullet::Update(float dt)
	{
		Actor::Update(dt);

		jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(transform.rotation);

		m_physicsComponent->SetVelocity(forward * speed * jojo::g_time.GetDeltaTime());


		transform.position += m_physicsComponent->velocity;


		transform.position.x = jojo::Wrap(transform.position.x, (float)jojo::g_renderer.GetWidth());


	}


	void Bullet::OnCollision(Actor* other)
	{
 		if (other->tag != tag)
		{
			lifespan = 0;
			m_destroyed = true;
		}
	}

	void Bullet::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}




