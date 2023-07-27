#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyFast.h";
#include "Heart.h"

#include "Framework/Emitter.h"
#include "Renderer/Renderer.h"
#include "../Audio/AudioSystem.h"
#include "../Input/InputSystem.h"
#include "Renderer/ModelManager.h"

#include "Framework/Scene.h"



bool kiko::SpaceGame::Initiliaze()
{
	//Initialize all texts and fonts
	m_UIfont = std::make_shared<Font>("Minecraft.otf", 30);
	m_titleFont = std::make_shared<Font>("Minecraft.otf", 50);

	m_scoreText = std::make_shared<Text>(m_UIfont);
	m_scoreText->Create(kiko::g_rend, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_livesText = std::make_shared<Text>(m_UIfont);
	m_livesText->Create(kiko::g_rend, "Hearts: ", kiko::Color{ 1,1,1,1 });

	m_titleText = std::make_shared<Text>(m_titleFont);
	m_titleText->Create(kiko::g_rend, "Asteroids", kiko::Color{ 1, 1, 1, 1 });
	
	m_gameOverText = std::make_shared<Text>(m_UIfont);
	m_gameOverText->Create(kiko::g_rend, "Game Over", kiko::Color{ 1,1,1,1 });
	
	m_funnyText = std::make_shared<Text>(m_UIfont);
	m_funnyText->Create(kiko::g_rend, "Mouse", kiko::Color{ 1,1,1,1 });

	

	//Load audio
	kiko::g_audSys.Initialize();
	kiko::g_audSys.AddAudio("hit", "Laser_Shoot.wav");
	//Initialize Scene
	m_scene = std::make_unique<kiko::Scene>();
	


	return true;
}

void kiko::SpaceGame::ShutDown()
{
}

void kiko::SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case kiko::SpaceGame::eState::Title:
		if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		/*m_scoreText->Draw(kiko::g_rend, 400, 300);
		m_titleText->Draw(kiko::g_rend, 200, 300);*/
		break;
	case kiko::SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;

		break;
	case kiko::SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(100.0f, 200.0f, kiko::Pi, kiko::Transform{ {300,400}, 0, 6 }, kiko::g_modMan.Get("SpaceShip.txt"));

		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}
		break;
	case kiko::SpaceGame::eState::Game:
		
		
		m_enemySpawnTimer += dt;
		m_enemyFastSpawnTimer += dt;
		m_heartSpawnTimer += dt;
		kiko::g_audSys.Update();
		

		for (auto& actor : m_scene->m_actors)
		{
			if(actor->m_destroyed && actor->m_tag != "Laser" && actor->m_tag != "Heart")
			{
				do
				{
					m_emitTimer += dt;
					EmitAtDeath(actor->GetPosition(), dt);
				} while (m_emitTimer >= m_spawnTime - 2.5f);
			}
			if (actor->m_destroyed && actor->m_tag == "Heart")
			{
				do
				{
					m_collectEmitTimer += dt;
					EmitAtCollect(actor->GetPosition(), dt);


				} while (m_collectEmitTimer >= m_spawnTime - 2.8f);
			}

		}
		
		if (m_enemySpawnTimer >= m_spawnTime)
		{
			m_enemySpawnTimer = 0;
			
			
			//Fix Where They Spawn

			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::random(kiko::g_rend.GetHeight()),kiko::random(kiko::g_rend.GetWidth())}, 0, 6 }, kiko::g_modMan.Get("EnemyShip.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		if (m_enemyFastSpawnTimer >= m_spawnTime + 10 )
		{
			m_enemyFastSpawnTimer = 0;
			
			
			std::unique_ptr<EnemyFast> enemyF = std::make_unique<EnemyFast>(kiko::randomf(150.0f, 195.0f), kiko::Pi, kiko::Transform{ {kiko::random(kiko::g_rend.GetHeight()),kiko::random(kiko::g_rend.GetWidth())}, 0, 6 }, kiko::g_modMan.Get("EnemyFastShip.txt"));
			enemyF->m_tag = "Enemy";
			enemyF->m_game = this;
			m_scene->Add(std::move(enemyF));
			//Fix Where They Spawn

		}
		if (m_heartSpawnTimer >= m_spawnTime + 6)
		{
			m_heartSpawnTimer = 0;
			std::unique_ptr<Heart> heart = std::make_unique<Heart>(kiko::Transform{ {kiko::random(kiko::g_rend.GetHeight()), kiko::random(kiko::g_rend.GetWidth())}, 0, 6 }, kiko::g_modMan.Get("HeartContainer.txt"));
			heart->m_tag = "Heart";
			heart->m_game = this;
			m_scene->Add(std::move(heart));

		}
		
		
		

		
		
		break;
	case kiko::SpaceGame::eState::PlayerDeadStart:
		m_stateTimer = 3;
		m_emitTimer = 0;
		for (auto& actor : m_scene->m_actors)
		{
			if (actor->m_tag == "Player") 
			{
				do
				{
					EmitAtDeath(actor->GetPosition(), dt);
				} while (m_emitTimer >= m_spawnTime - 2.5f);
			}
		}
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case kiko::SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) 
		{
			m_state = eState::StartLevel;

			
		}
		
		break;
	case kiko::SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;


		}
		break;
	default:
		break;
	}
	m_scoreText->Create(kiko::g_rend, "Score: " + std::to_string(m_score), {1, 1, 1, 1});
	m_livesText->Create(kiko::g_rend, "Lives: " + std::to_string(m_lives), { 1, 1, 1, 1 });
	g_partSys.Update(dt);
	m_scene->Update(dt);
}

void kiko::SpaceGame::Draw(Renderer& rend)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(rend, 275, 300);
		m_funnyText->DrawV(rend, kiko::g_inSys.GetMousePosition());

	}
	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(rend, 400, 300);
	}
	if (m_state == eState::Game) {
		m_livesText->Draw(rend, 40, 500);
	}
	m_scoreText->Draw(rend, 40, 40);
	g_partSys.Draw(rend);
	m_scene->Draw(rend);
}
void kiko::SpaceGame::EmitAtDeath(Vector2& pos, float dt)
{
	
	EmitterData data;
	data.burst = true;
	data.burstCount = 50;
	data.spawnRate = 100;
	data.angle = 0;
	data.angleRange = kiko::Pi;
	data.lifetimeMin = 0.5f;
	data.lifetimeMax = 1.5f;
	data.speedMin = 50;
	data.speedMax = 250;
	data.damping = 0.5f;
	data.color = kiko::Color{ 1, 1, 1, 1 };
	Transform transform{ pos, 0, 1 };
	auto emitter = std::make_unique<Emitter>(transform, data);
	emitter->m_lifespan = .5f;
	m_scene->Add(std::move(emitter));

	

}
void kiko::SpaceGame::EmitAtCollect(Vector2& pos, float dt)
{

	EmitterData data;
	data.burst = true;
	data.burstCount = 25;
	data.spawnRate = 10;
	data.angle = 0;
	data.angleRange = kiko::Pi;
	data.lifetimeMin = 0.5f;
	data.lifetimeMax = 1.5f;
	data.speedMin = 50;
	data.speedMax = 250;
	data.damping = 0.5f;
	data.color = kiko::Color{ 0, 1, 0, 1 };
	Transform transform{ pos, 0, 1 };
	auto emitter = std::make_unique<Emitter>(transform, data);
	emitter->m_lifespan = .1f;
	m_scene->Add(std::move(emitter));



}
