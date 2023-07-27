#include "../Source/Engine/Core/Core.h"
#include "Renderer/Renderer.h"
#include "../Input/InputSystem.h"
#include "../Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Emitter.h"
#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;
};



int main(int argc, char* argv[])
{
	std::unique_ptr<int> up = std::make_unique<int>(10);
	
	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");
	

	kiko::g_rend.Initialize();
	kiko::g_rend.CreateWindow("Kurwa", 800, 600);
	kiko::g_inSys.Initialize();
	
	
	
	


	


	unique_ptr<kiko::SpaceGame> game = make_unique<kiko::SpaceGame>();
	game->Initiliaze();
	




	kiko::Vector2 v2{ 300, 500 };


	kiko::Vector2 position{ 400, 300 };
	kiko::Transform trans{ {400, 300}, 0, 3 };
	float speed = 200;
	constexpr float turnRate = kiko::DegreesToRadians(180.0f);

	v2.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 100; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_rend.GetWidth()), kiko::random(kiko::g_rend.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}
	

	// Main game loop
	bool quit = false;
	while (!quit)
	{
		//update engine
		kiko::g_time.Tick();
		kiko::g_inSys.Update();
		//kiko::g_partSys.Update(kiko::g_time.GetDeltaTime());

		
		

		// update game

		if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

		
		game->Update(kiko::g_time.GetDeltaTime());
		
		
		
		kiko::g_rend.SetColor(0, 0, 0, 0);
		kiko::g_rend.BeginFrame();
		
		// draw game
		for (auto& star : stars)
		{
			
			star.Update(kiko::g_rend.GetWidth(), kiko::g_rend.GetHeight());

			kiko::g_rend.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			
			star.Draw(kiko::g_rend);
			
			

		}		
		game->Draw(kiko::g_rend);
		//kiko::g_partSys.Draw(kiko::g_rend);
		
		
		kiko::g_rend.EndFrame();
	}
	game->ShutDown();
	kiko::MemoryTracker::DisplayInfo();
	


	return 0;
		
}
		

