#include "Audio/AudioSystem.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Core/Logger.h"

#include "PlatformGame.h"


#include "Physics/PhysicsSystem.h"

#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <array>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
	//jojo::Factory::Instance().Register<jojo::Sprite>("Sprite");

	INFO_LOG("Initalize Engine");

	jojo::MemoryTracker::Initialize();
	jojo::seedRandom((unsigned int)time(nullptr));
	jojo::setFilePath("Assets");// /Platform 

	jojo::g_renderer.Initalize();
	jojo::g_renderer.CreateWindow("CSC196", 800, 600);

	jojo::g_inputSystem.Initialize();
	jojo::g_audioSystem.Initialize();
	jojo::PhysicsSystem::Instance().Initialize();


	unique_ptr<PlatformGame> game = std::make_unique<PlatformGame>();
	game->Initalize();


	//Main game loop
	bool quit = false;
	while (!quit)
	{
		jojo::g_time.Tick();
		jojo::g_inputSystem.Update();
		if (jojo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		jojo::g_particleSystem.Update(jojo::g_time.GetDeltaTime());
		jojo::ParticleSystem::Instance().Update(jojo::g_time.GetDeltaTime());
		//jojo::g_audioSystem.Update();


		game->Update(jojo::g_time.GetDeltaTime());

		jojo::g_renderer.SetColor(0, 0, 0, 0);
		jojo::g_renderer.BeginFrame();

		game->Draw(jojo::g_renderer);

		jojo::g_particleSystem.Draw(jojo::g_renderer);

		jojo::g_renderer.EndFrame();
	}

	jojo::g_audioSystem.Shutdown();
	jojo::MemoryTracker::DisplayInfo();

	return 0;
}