#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"

#include "Framework/Framework.h"

#include "Core/Logger.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"





bool SpaceGame::Initalize()
{

	//create font
	m_font = GET_RESOURCE(jojo::Font, "ArcadeClassic.ttf", 24);

	std::unique_ptr<jojo::Text> text = std::make_unique<jojo::Text>(m_font);
	text->Create(jojo::g_renderer, "NEUMONT", jojo::Color{ 81, 90, 1, 255 });

	m_scoreText = std::make_unique<jojo::Text>(m_font);
	m_highscoreText = std::make_unique<jojo::Text>(m_font);
	m_scoreText->Create(jojo::g_renderer, "ooooo", jojo::Color{ 1, 90, 71, 255 });

	m_titleText = std::make_unique<jojo::Text>(m_font);
	m_titleText->Create(jojo::g_renderer, "SPACE GAME", jojo::Color{ 91, 1, 1, 255 });

	m_addText = std::make_unique<jojo::Text>(m_font);
	

	//Load Audio
	jojo::g_audioSystem.AddAudio("laser", "Audio/laser.wav");
	jojo::g_audioSystem.AddAudio("hit", "Audio/hit.wav");
	jojo::g_audioSystem.AddAudio("gameover", "Audio/GameOver.wav");
	jojo::g_audioSystem.AddAudio("gameplay", "Audio/gameplay.wav");
	jojo::g_audioSystem.AddAudio("intro", "Audio/Intro.wav");
	jojo::g_audioSystem.AddAudio("over", "Audio/over.wav");

	//scene
	m_scene = std::make_unique<jojo::Scene>();

	m_scene->Load("Scenes/spacescene.json");
	m_scene->Initialize();


	//m_scene->GetActorByName("Title")->active = true; 

	//EVENT_SUBSCRIBE("Add Points", SpaceGame::addPoints);
	//EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

    return true;
}

bool SpaceGame::Shutdown()
{
    return false;
}

void SpaceGame::Update(float dt)
{

	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_X) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_X))
		{
			m_state = eState::StartGame;

		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		//creatplayer
		auto player = INSTANTIATE(Player, "Player");
		player->transform = jojo::Transform{ { 400, 300 }, 0, 10 };
		player->Initialize();
		player->m_game = this;
		m_scene->Add(std::move(player));

	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform = jojo::Transform{ { jojo::random(100,800), jojo::random(100,600)}, 0, 8};
			enemy->Initialize();
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
			m_spawnTimer = 0;

		}
		m_spawnAsteroidTimer += dt;
		if (m_spawnAsteroidTimer >= m_spawnTimeAsteroid)
		{
			auto asteroid = INSTANTIATE(Asteroid, "Asteroid");
			asteroid->transform = jojo::Transform{ { jojo::random(100,800), 50 }, 0, 11 };
			asteroid->Initialize();
			asteroid->m_game = this;
			m_scene->Add(std::move(asteroid));

			m_spawnAsteroidTimer = 0;
			m_spawnTimeAsteroid = jojo::randomf(5.0f, 10.0f);
		}

		if (m_scene->GetActorByName("Player")->health <= 0)	this->SetState(SpaceGame::eState::PlayerDeadStart);

		break;
	case eState::PlayerDeadStart:
		m_scene->RemoveAll();
		m_stateTimer = 3;
		m_state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}

	m_scoreText->Create(jojo::g_renderer, "Score  " + std::to_string(m_score) + "          " + "Lives  " + std::to_string(GetLives()), {201,100,10,255});
	m_highscoreText->Create(jojo::g_renderer, "HIGHSCORE  " + jojo::loadFile("highscore.txt"), {218,0,218,255});
	m_scene->Update(dt); 
}

void SpaceGame::Draw(jojo::Renderer& renderer)
{
	if (m_state == eState::Title) {
		m_addText->Create(jojo::g_renderer, "Press  X  to  Start  Game", jojo::Color{ 91, 1, 1, 255 });

		m_titleText->Draw(renderer, 340, 270);
		m_addText->Draw(renderer, 280, 300);
		m_scoreText->Draw(renderer, 290, 500);
		m_highscoreText->Draw(renderer, 310, 100);


	}
	else if (m_state == eState::GameOver)
	{
		m_titleText->Create(jojo::g_renderer, "Game  Over", { 255,0,0,255 });
		m_addText->Create(jojo::g_renderer, "Press  R  to  Restart  or  Esc  to  leave", jojo::Color{ 255, 0, 0, 255 });
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_R) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_R)) m_state = eState::StartGame;
		m_titleText->Draw(renderer,320, 350);
		m_addText->Draw(renderer,180, 400);
		if (m_score > std::stoi(jojo::loadFile("highscore.txt")))
		{
			std::string input = std::to_string(GetScore());
			jojo::writeFile("highscore.txt", input);
		}
		m_highscoreText->Draw(renderer, 290, 100);
		
	}
	else
	{
		m_scene->Draw(renderer);//draw this first - possible fix
		m_scoreText->Draw(renderer, 290, 500);
	}
}


void SpaceGame::addPoints(const jojo::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const jojo::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
