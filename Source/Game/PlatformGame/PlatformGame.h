#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Core/Random.h"
#include "Framework/Event/EventManager.h"



class PlatformGame : public jojo::Game
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
	void OnPlayerDead(const jojo::Event& event);

	friend class Game;

	eState m_state = eState::Title;
protected:
	float m_spawnTimer = 0;
	float m_spawnTime = 5;

	float rockTimer = 0;
	float rockTime = 5;

	float m_stateTimer = 0;
};