#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"

#include "Framework/Scene.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Emitter.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initalize()
{

	//create font
	std::shared_ptr<jojo::Font> font = std::make_shared<jojo::Font>("ArcadeClassic.ttf", 24);
	std::unique_ptr<jojo::Text> text = std::make_unique<jojo::Text>(font);
	text->Create(jojo::g_renderer, "NEUMONT", jojo::Color{ 81, 90, 1, 255 });
	m_font = font;

	m_scoreText = std::make_unique<jojo::Text>(font);
	m_highscoreText = std::make_unique<jojo::Text>(font);
	m_scoreText->Create(jojo::g_renderer, "ooooo", jojo::Color{ 1, 90, 71, 255 });

	m_titleText = std::make_unique<jojo::Text>(font);
	m_titleText->Create(jojo::g_renderer, "SPACE GAME", jojo::Color{ 91, 1, 1, 255 });

	m_addText = std::make_unique<jojo::Text>(font);
	

	//Load Audio
	jojo::g_audioSystem.AddAudio("laser", "laser.wav");
	jojo::g_audioSystem.AddAudio("hit", "hit.wav");
	jojo::g_audioSystem.AddAudio("gameover", "GameOver.wav");
	jojo::g_audioSystem.AddAudio("gameplay", "gameplay.wav");
	jojo::g_audioSystem.AddAudio("intro", "Intro.wav");
	jojo::g_audioSystem.AddAudio("over", "over.wav");

	//scene
	m_scene = std::make_unique<jojo::Scene>();


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
		std::unique_ptr<Player> player = std::make_unique<Player>(Player::Player(200, jojo::Pi, jojo::Transform({ 400,300 }, 0, 6), jojo::g_modelManager.Get("ship.txt")));
		player->m_health = 100;
		player->m_tag = "Player";
		player->SetDampening(1);
		player->m_game = this;
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(Enemy::Enemy(jojo::randomf(75.0f, 150.0f), jojo::Pi, jojo::Transform({ 400 + jojo::random(1,300),300 + jojo::random(1,300)}, 0, 3), jojo::g_modelManager.Get("enemyShip.txt")));
			enemy->m_tag = "Enemy";
			enemy->SetDampening(1);
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));

		}
		m_spawnAsteroidTimer += dt;
		if (m_spawnAsteroidTimer >= m_spawnTimeAsteroid)
		{
			m_spawnAsteroidTimer = 0;
			m_spawnTimeAsteroid = jojo::randomf(5.0f, 10.0f);
			std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(jojo::randomf(20.0f, 150.0f), 0, jojo::Transform{{jojo::random(10, 700), 0}, 0, 6}, jojo::g_modelManager.Get("Asteroid.txt"));
			asteroid->m_tag = "Enemy";
			asteroid->SetDampening(1);
			asteroid->m_game = this;
			m_scene->Add(std::move(asteroid));
		}

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

	m_scoreText->Create(jojo::g_renderer, "Score  " + std::to_string(m_score) + "          " + "Lives  " + std::to_string(GetLives()), {21,91,1,255});
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

		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_P) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_P))
		{
			jojo::g_audioSystem.PlayOneShot("gameplay", true);
			//jojo::g_audioSystem.PlayOneShot("intro", false);
		}

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

		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_P) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_P))
		{
			//jojo::g_audioSystem.PlayOneShot("gameover", false);
			//jojo::g_audioSystem.PlayOneShot("over", false);
		}

		
	}
	else
	{
		m_scoreText->Draw(renderer, 290, 500);
		m_scene->Draw(renderer);
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_P) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_P))
		{
			//jojo::g_audioSystem.PlayOneShot("gameplay", true);
		}
	}

	

}
