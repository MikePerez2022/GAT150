#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "..\Engine\Audio\AudioSystem.h"
#include "Framework/Scene.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include "SpaceGame.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Emitter.h"

#include "Core/Logger.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

using namespace std;



class Star
{
public:
	Star(jojo::Vector2& pos, jojo::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}

	void Update(int width, int height)
	{
		m_pos += m_vel * jojo::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(jojo::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	jojo::vec2 m_pos;
	jojo::vec2 m_vel;
};

int main(int argc, char* argv[])
{
	INFO_LOG("hello world");


	jojo::MemoryTracker::Initialize();
	jojo::seedRandom((unsigned int)time(nullptr));
	jojo::setFilePath("assets");


	jojo::g_renderer.Initalize();
	jojo::g_renderer.CreateWindow("CSC196", 800, 600); 

	jojo::g_inputSystem.Initialize();
	jojo::g_audioSystem.Initialize();


	unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initalize();

	vector<Star> Stars; 
	vector<jojo::Vector2> points;
	for (int i = 0; i < 1000; i++)
	{
		jojo::Vector2 pos(jojo::random(jojo::g_renderer.GetWidth()), jojo::random(jojo::g_renderer.GetHeight()));
		jojo::Vector2 vel(jojo::randomf(100,400), 0.0f);
		Stars.push_back(Star(pos, vel));
	}

	

	//Main game loop
	bool quit = false;	
	while (!quit) 
	{
		jojo::g_time.Tick();

		jojo::g_inputSystem.Update();
				
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		jojo::g_audioSystem.Update();

		game->Update(jojo::g_time.GetDeltaTime());

		jojo::g_particleSystem.Update(jojo::g_time.GetDeltaTime());
		
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !jojo::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			jojo::g_audioSystem.PlayOneShot("laser", false);
		}

		jojo::g_renderer.SetColor(0, 0, 0, 0);
		jojo::g_renderer.BeginFrame();

		//draw
		game->Draw(jojo::g_renderer);
		jojo::g_particleSystem.Draw(jojo::g_renderer);
				
		jojo::Vector2 vel(1.0f, 0.3f);
		for (auto& star : Stars)
		{
			star.Update(jojo::g_renderer.GetWidth(), jojo::g_renderer.GetHeight());
			jojo::g_renderer.SetColor(jojo::random(256), jojo::random(256), jojo::random(256), 200);
			star.Draw(jojo::g_renderer);
		}

		jojo::g_renderer.EndFrame();		
	}
	
	Stars.clear();
	jojo::g_audioSystem.Shutdown(); 
	jojo::MemoryTracker::DisplayInfo();

	return 0;
}