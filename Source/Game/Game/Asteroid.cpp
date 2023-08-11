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

bool Asteroid::Initalize()
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

void Asteroid::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();

	jojo::vec2 direction = m_transform.position - player->m_transform.position;

	m_transform.rotation = direction.Angle() * jojo::HalfPi;
	m_transform.rotation = m_transform.rotation * 4 * jojo::g_time.GetDeltaTime();

	jojo::vec2 forward = jojo::vec2{ 0,1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * 1 * jojo::g_time.GetDeltaTime();
	//m_transform.position += forward * m_speed * jojo::g_time.GetDeltaTime();
	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());

}

void Asteroid::OnCollision(Actor* other)
{

	if (other->m_tag == "Player")
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
		jojo::Transform transform{ m_transform.position, 0, 6 };
		auto emitter = std::make_unique<jojo::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));

		jojo::g_audioSystem.PlayOneShot("hit", false);
	}

	if (m_game->m_score <= 0)
	{
		m_game->m_score = 0;
	}
}