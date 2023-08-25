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

	//scene
	m_scene = std::make_unique<jojo::Scene>();

	m_scene->Load("Scenes/platformscene.json");
	m_scene->Initialize();


	m_scene->GetActorByName("Title")->active = true;

	//EVENT_SUBSCRIBE("Add Points", SpaceGame::addPoints);
	//EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

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
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_X) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_X))
		{
			m_state = eState::StartGame;

		}
		break;
	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		{

		}
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:


		if (m_scene->GetActorByName("Player")->health <= 0)	this->SetState(PlatformGame::eState::PlayerDeadStart);

		break;
	case eState::PlayerDeadStart:
		m_scene->RemoveAll();
		m_stateTimer = 3;
		m_state = eState::PlayerDead;
		break;
	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			if (m_lives == 0) m_state = eState::GameOver;
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


void PlatformGame::addPoints(const jojo::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const jojo::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
