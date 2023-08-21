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
			float scale = transform.scale;
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
	transform.rotation += rotate * m_turnRate * jojo::g_time.GetDeltaTime();


	float thrust = 0;
	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust * dt);


	transform.position.x = jojo::Wrap(transform.position.x, (float)jojo::g_renderer.GetWidth());
	transform.position.y = jojo::Wrap(transform.position.y, (float)jojo::g_renderer.GetHeight());

	
	// fire
	m_coolDownTimer += dt;
	if (m_coolDownTimer >= m_coolDown && jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		auto bullet = INSTANTIATE(Bullet, "Rocket");
		bullet->transform = { transform.position, transform.rotation - jojo::DegreesToRadians(5), 5 };
		bullet->Initalize();
		m_scene->Add(std::move(bullet));
		
	}

	if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_T) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_T)) jojo::g_time.SetTimescale(0.5f);
	else jojo::g_time.SetTimescale(1.0f);
	
}

void Player::OnCollision(Actor* other)
{
	if (other->tag == "Enemy")
	{
		health -= 25; //4 hits

		if (health <= 0) 
		{
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			m_destroyed = true;
		}

		jojo::g_audioSystem.PlayOneShot("hit", false);
		
	}

}

