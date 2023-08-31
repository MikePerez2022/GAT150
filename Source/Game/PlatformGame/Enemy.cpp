#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Player.h"


namespace jojo
{
	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		//Cache
		m_physicsComponent = GetComponent<jojo::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float dt)
	{
		Enemy::Update(dt);

		float dir = 0;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		jojo::vec2 forward = jojo::vec2{ 1, 0 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

		m_physicsComponent->ApplyForce(forward * speed * dir);

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			health -= 25; //4 hits

			if (health <= 0)
			{
				m_destroyed = true;
			}

			jojo::g_audioSystem.PlayOneShot("hit", false);

		}

	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		
	}

	void Enemy::Read(const rapidjson::Value& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
		READ_DATA(value, health);
	}


}



