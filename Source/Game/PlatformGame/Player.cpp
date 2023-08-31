#include "Player.h"

#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"


namespace jojo
{
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();

		//Cache
		m_physicsComponent = GetComponent<jojo::PhysicsComponent>();
		m_spriteAnim = GetComponent<jojo::SpriteAnim>();


		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);


		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->velocity;


		float dir = 0;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		if (dir)
		{
			jojo::vec2 forward = jojo::vec2{ 1, 0 };
			velocity.x += speed * dir * ((onGround) ? 1 : 0.2f) * dt;
			velocity.x = Clamp(velocity.x, -maxspeed, maxspeed);
			//m_physicsComponent->SetVelocity(velocity);

			m_physicsComponent->ApplyForce(forward * speed * dir);
		}

		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			jojo::vec2 up = jojo::vec2{ 0,-1 };

			m_physicsComponent->SetVelocity((up * jump));// velocity + ()
		}

		//m_physicsComponent->SetGravityScale((velocity.y > 0) ? 5.0f : 3.0f);

		//
		if (std::fabs(velocity.x) > 0.2f)
		{
			if(dir != 0) m_spriteAnim->flipH = (dir < 0);
			m_spriteAnim->SetSequence("run");
		}
		else
		{
			m_spriteAnim->SetSequence("idle");
		}

	}

	void Player::OnCollisionEnter(Actor* other)
	{

		if (other->tag == "Enemy")
		{
			health -= 25;

			if (health <= 0)
			{
				//m_destroyed = true;
			}

			jojo::g_audioSystem.PlayOneShot("hit", false);

		}
		if (other->tag == "Ground") groundCount++;

	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Player::Read(const rapidjson::Value& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
		READ_DATA(value, health);
		READ_DATA(value, maxspeed);
	}


}



