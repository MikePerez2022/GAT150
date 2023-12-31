#include "Asteroid.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Bullet.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Core/Random.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"

namespace jojo
{
	CLASS_DEFINITION(Asteroid);

	bool Asteroid::Initalize()
	{
		Actor::Initialize();

		auto collisionComponent = GetComponent<jojo::CollisionComponent>();

		if (collisionComponent)
		{
			auto renderComponent = GetComponent<jojo::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->radius = GetComponent<jojo::RenderComponent>()->GetRadius() / scale;
			}
		}

		return true;
	}

	void Asteroid::Update(float dt)
	{
		Actor::Update(dt);

		jojo::Player* player = m_scene->GetActor<jojo::Player>();

		jojo::vec2 direction = transform.position - player->transform.position;

		transform.rotation = direction.Angle() * jojo::HalfPi;
		transform.rotation = transform.rotation * 4 * jojo::g_time.GetDeltaTime();

		jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(transform.rotation);
		transform.position += forward * speed * 1 * jojo::g_time.GetDeltaTime();
		//m_transform.position += forward * m_speed * jojo::g_time.GetDeltaTime();
		transform.position.x = jojo::Wrap(transform.position.x, (float)jojo::g_renderer.GetWidth());

	}

	void Asteroid::OnCollision(Actor* other)
	{

		if (other->tag == "Player")
		{
			m_game->RemovePoints(50);
			m_destroyed = true;

			jojo::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = jojo::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = jojo::Color{ 200, 0, 0, 255 };
			jojo::Transform transform{ this->transform.position, 0, 6 };
			auto emitter = std::make_unique<jojo::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));

			jojo::g_audioSystem.PlayOneShot("hit", false);
		}

		if (m_game->m_score <= 0)
		{
			m_game->m_score = 0;
		}
	}

	void Asteroid::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}

