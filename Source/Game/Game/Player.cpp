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
#include "Framework/Event/EventManager.h"
#include "Framework/Components/PhysicsComponent.h"

//CLASS_DEFINITION(Player);
namespace jojo
{
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		//Cache
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

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		float rotate = 0;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;


		transform.rotation += rotate * turnRate * jojo::g_time.GetDeltaTime();


		float thrust = 0;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		jojo::vec2 forward = jojo::vec2{ 0,-1 }.Rotate(transform.rotation);

		//auto physicsComponent = GetComponent<jojo::PhysicsComponent>();
		//physicsComponent->ApplyForce(forward * speed * thrust * dt);

		//m_physicsComponent->ApplyForce(forward * speed * thrust * dt);
		//m_physicsComponent->ApplyTorque(5);


		transform.position.x = jojo::Wrap(transform.position.x, (float)jojo::g_renderer.GetWidth());
		transform.position.y = jojo::Wrap(transform.position.y, (float)jojo::g_renderer.GetHeight());


		// fire
		m_coolDownTimer += dt;
		if (m_coolDownTimer >= m_coolDown && jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
 			auto bullet = INSTANTIATE(Bullet, "Rocket");
			bullet->transform = { transform.position + forward * 30, transform.rotation - jojo::DegreesToRadians(5), 5 };
			bullet->Initalize();
			bullet->active = true;
			m_scene->Add(std::move(bullet));

			m_coolDownTimer = 0;

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
				//jojo::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
				//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
				
				m_game->SetLives(m_game->GetLives() - 1);
				m_destroyed = true;
				//SpaceGame::eState::PlayerDeadStart;
			}

			jojo::g_audioSystem.PlayOneShot("hit", false);

		}

	}

	void Player::Read(const rapidjson::Value& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
		READ_DATA(value, health);
	}


}



