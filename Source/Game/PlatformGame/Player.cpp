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
		m_physicsComponent = GetComponent<jojo::Box2DPhysicsComponent>(); \
		m_spriteAnim = GetComponent<jojo::SpriteAnim>();


		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);


		vec2 velocity = m_physicsComponent->velocity;


		float dir = 0;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		if (dir)
		{
			jojo::vec2 forward = jojo::vec2{ 1, 0 };

			m_physicsComponent->ApplyForce(forward * speed * dir);
		}


		//Jump
		if (Jumpcount == 0 && jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			jojo::vec2 up = jojo::vec2{ 0,-1 };

			m_physicsComponent->SetVelocity(up * jump);

			m_spriteAnim->SetSequence("jump");

			Jumpcount++;
			
			m_physicsComponent->SetGravityScale(1.05);
		}

		

		if (Jumpcount > 0)
		{
			jumpTimer += dt;
		}
		if (jumpTimer >= jumpTime)
		{
			Jumpcount = 0;
			jumpTimer = 0;
			m_physicsComponent->SetGravityScale(1);
		}
		


		//Animation
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

	void Player::OnCollision(Actor* other)
	{
		if (other->tag == "Enemy" || other->tag == "Rock")
		{
			health -= 50;

			if (health <= 0) 
			{
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
				data.color = jojo::Color{ 255, 0, 0, 255 };
				jojo::Transform transform{ this->transform.position, 0, 6 };
				auto emitter = std::make_unique<jojo::Emitter>(transform, data);
				emitter->lifespan = 1.0f;
				m_scene->Add(std::move(emitter));

				jojo::g_audioSystem.PlayOneShot("hit", false);

				m_destroyed = true;
			}


			

		}

		if (other->tag == "Health" && health != 100)
		{
			health += 50;
			m_scene->GetActorByName("Health")->active = false;
		}

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



