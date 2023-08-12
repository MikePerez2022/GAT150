#include "Audio/AudioSystem.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "Core/Logger.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <array>
#include <map>

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

void print(int count, ...)
{
	va_list args;

	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}

int main(int argc, char* argv[])
{
	INFO_LOG("Initalize Engine");

	jojo::MemoryTracker::Initialize();
	jojo::seedRandom((unsigned int)time(nullptr));
	jojo::setFilePath("assets");

	rapidjson::Document document;
	jojo::Json::Load("json.txt", document);

	int i1;
	jojo::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	jojo::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;

	std::string str;
	jojo::Json::Read(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	jojo::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;

	float f;
	jojo::Json::Read(document, "float", f);
	std::cout << f << std::endl;

	jojo::vec2 v2;
	jojo::Json::Read(document, "vector2", v2);
	std::cout << v2 << std::endl;

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

	// create texture
	jojo::res_t<jojo::Texture> texture = jojo::g_resources.Get<jojo::Texture>("newship.PNG", jojo::g_renderer);

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