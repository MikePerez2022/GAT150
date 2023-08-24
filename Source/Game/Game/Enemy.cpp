#include "Enemy.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Bullet.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Framework/Components/EnginePhysicsComponent.h"
#include "Framework/Components/CircleCollisionComponent.h"
#include "Framework/Components/RenderComponent.h"
#include "Framework/Event/EventManager.h"
#include "Physics/PhysicsSystem.h"

namespace jojo
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initalize()
	{
		Actor::Initialize();

		//m_physicsComponent = GetComponent<jojo::PhysicsComponent>();

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

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(transform.rotation);
		if (m_scene->GetActorByName("Player"))
		{
			jojo::vec2 direction = transform.position - m_scene->GetActorByName("Player")->transform.position;

			float turnAngle = jojo::vec2::SignedAngle(forward, direction.Normalized());

			//m_physicsComponent->ApplyTorque(turnAngle);

			transform.rotation += turnAngle * 5 * dt;
			transform.rotation = direction.Angle() * jojo::HalfPi;

			float angle = jojo::vec2::Angle(forward, direction.Normalized());

			if (std::fabs(turnAngle) < jojo::DegreesToRadians(30.0f))
			{
				//
			}
		}

		transform.position += forward * speed  * jojo::g_time.GetDeltaTime();


		transform.position.x = jojo::Wrap(transform.position.x, (float)jojo::g_renderer.GetWidth());
		transform.position.y = jojo::Wrap(transform.position.y, (float)jojo::g_renderer.GetHeight());

		/*
		if (m_fireTimer <= 0) {
			jojo::Transform transform{transform.position, 0, transform.scale};
			std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(Bullet{ 200, transform});
			bullet->tag = "Enemy";
			m_scene->Add(std::move(bullet));

			m_fireTimer = 2.0f;
		}
		*/
	}

	void Enemy::OnCollision(Actor* other)
	{

		if (other->tag == "Player")
		{
			//jojo::EventManager::Instance().DispatchEvent("Add Points", 100);
			m_game->AddPoints(100);
			m_destroyed = true;

			jojo::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = jojo::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMax = 1.5f;
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
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}


