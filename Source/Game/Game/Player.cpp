#include "Player.h"
#include "SpaceGame.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "..\Game\Bullet.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Components/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/CircleCollisionComponent.h"

bool Player::Initialize()
{
	Actor::Initialize();

	//Cache
	m_physicsComponent = GetComponent<jojo::PhysicsComponent>();
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

void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * jojo::g_time.GetDeltaTime();


	float thrust = 0;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(m_transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust * dt);


	m_transform.position.x = jojo::Wrap(m_transform.position.x, (float)jojo::g_renderer.GetWidth());
	m_transform.position.y = jojo::Wrap(m_transform.position.y, (float)jojo::g_renderer.GetHeight());

	// fire
	m_coolDownTimer += dt;
	if (m_coolDownTimer >= m_coolDown && jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		jojo::Transform transform{m_transform.position, m_transform.rotation - jojo::DegreesToRadians(5), 5};
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>( Bullet{ 350, transform});//
		bullet->m_tag = "Player";
		//
		std::unique_ptr<jojo::Sprite> component = std::make_unique<jojo::Sprite>();
		component->m_texture = jojo::g_resources.Get<jojo::Texture>("bullet.png", jojo::g_renderer);
		bullet->AddComponent(std::move(component));
		//
		auto collisionComponent = std::make_unique<jojo::CircleCollisionComponent>();
		collisionComponent->m_radius = 3.0f;
		bullet->AddComponent(std::move(collisionComponent));

		bullet->Initialize();
		m_scene->Add(std::move(bullet));

		jojo::Transform transform2{m_transform.position, m_transform.rotation + jojo::DegreesToRadians(5), 5};
		bullet = std::make_unique<Bullet>(Bullet{ 350, transform2});//
		bullet->m_tag = "Player";
		//
		component = std::make_unique<jojo::Sprite>();
		component->m_texture = jojo::g_resources.Get<jojo::Texture>("bullet.png", jojo::g_renderer);
		bullet->AddComponent(std::move(component));
		//
		collisionComponent = std::make_unique<jojo::CircleCollisionComponent>();
		collisionComponent->m_radius = 3.0f;
		bullet->AddComponent(std::move(collisionComponent));

		bullet->Initialize();
		m_scene->Add(std::move(bullet));

		m_coolDownTimer = 0;
		
	}

	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_T) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_T)) jojo::g_time.SetTimescale(0.5f);
	else jojo::g_time.SetTimescale(1.0f);
	
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy")
	{
		m_health -= 25; //4 hits

		if (m_health <= 0) 
		{
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			m_destroyed = true;
		}

		jojo::g_audioSystem.PlayOneShot("hit", false);
		
	}

}

