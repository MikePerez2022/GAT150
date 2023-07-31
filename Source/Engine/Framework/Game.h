#pragma once
#include <memory>

namespace jojo
{
	class Renderer;

	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initalize() = 0;
		virtual bool Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }
		void RemovePoints(int points) { m_score -= points; }

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }

		friend class SpaceGame;
		friend class Asteroid;

	protected:
		std::unique_ptr<class Scene> m_scene;

		int m_score = 0;
		int m_lives = 0;
	};
}