#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Core/Random.h"

class SpaceGame : public jojo::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOver,
	};

public:

	virtual bool Initalize() override;
	virtual bool Shutdown() override;
	virtual void Update(float dt) override;
	virtual void Draw(jojo::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

	friend class Game;

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnAsteroidTimer = 0;
	float m_spawnTime = 3;
	float m_spawnTimeAsteroid = 5;

	float m_stateTimer = 0;

	std::shared_ptr<jojo::Font> m_font;
	std::unique_ptr<jojo::Text> m_scoreText;
	std::unique_ptr<jojo::Text> m_highscoreText;
	std::unique_ptr<jojo::Text> m_titleText;
	std::unique_ptr<jojo::Text> m_addText;
};