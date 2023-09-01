#include "PlatformGame.h"

#include "Framework/Framework.h"

#include "Core/Logger.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"





bool PlatformGame::Initalize()
{
	//Load Audio
	jojo::g_audioSystem.AddAudio("hit", "Audio/hit.wav");
	jojo::g_audioSystem.AddAudio("GameOver", "Audio/GameOver.wav");
	jojo::g_audioSystem.AddAudio("Collapse", "Audio/Collapse.wav");
	jojo::g_audioSystem.AddAudio("Level", "Audio/Level.wav");
	
	//scene
	m_scene = std::make_unique<jojo::Scene>();

	switch (m_state) 
	{
	case PlatformGame::eState::Title:

		m_scene->Load("Scenes/StartScene.json");
		m_scene->Load("Scenes/tilemap_01.json");
		m_scene->Initialize();

		break;
	case PlatformGame::eState::StartLevel:

		m_scene->Load("Scenes/Level01.json");
		m_scene->Load("Scenes/tilemap_02.json");
		m_scene->Initialize();

		break;
	case PlatformGame::eState::GameOver:

		m_scene->Load("Scenes/GameOver.json");
		m_scene->Initialize();



		break;
	}


	return true;
}

bool PlatformGame::Shutdown()
{
	return false;
}

void PlatformGame::Update(float dt)
{

	switch (m_state)
	{
	case PlatformGame::eState::Title:	

		for (int i; m_score <= 3; m_score++)
		{
		auto actor = INSTANTIATE(Actor, "coin");
		actor->transform.position = { jojo::randomf(jojo::g_renderer.GetWidth(), 100.0f) };
		actor->Initialize();
		m_scene->Add(std::move(actor));
		}

		if(jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W)) jojo::g_audioSystem.PlayOneShot("Collapse", false);

		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_X) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_X))
		{
			m_state = eState::StartGame;

		}
		break;
	case PlatformGame::eState::StartGame:
		m_lives = 2;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			PlatformGame::Initalize();
		}
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:

		rockTimer += dt;
		if (rockTimer >= rockTime)
		{
			auto rock = INSTANTIATE(Actor, "Rock");
			rock->transform.position = { jojo::randomf(jojo::g_renderer.GetWidth(), 100.0f) };
			rock->Initialize();
			m_scene->Add(std::move(rock));

			rockTimer = 0;
			rockTime = jojo::random(10);
		}
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_P) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_P))
		{
			jojo::g_audioSystem.PlayOneShot("Level", true);

		}

		if (m_scene->GetActorByName("Player")->health <= 0)	this->SetState(PlatformGame::eState::PlayerDeadStart);

		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		m_state = eState::PlayerDead;
		break;
	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_lives--;
			if (m_lives == 0)
			{
				m_state = eState::GameOver;
				m_scene->RemoveAll();
				{
					jojo::g_audioSystem.PlayOneShot("GameOver", false);
					PlatformGame::Initalize();
				}
			}
			else m_state = eState::StartLevel;
		}
		break;
	case PlatformGame::eState::GameOver:
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void PlatformGame::Draw(jojo::Renderer& renderer)
{
	m_scene->Draw(renderer);
}



void PlatformGame::OnPlayerDead(const jojo::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
