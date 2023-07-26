#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"


#include "Renderer/Renderer.h"
#include "../Audio/AudioSystem.h"
#include "../Input/InputSystem.h"
#include "Renderer/ModelManager.h"

#include "Framework/Scene.h"



bool kiko::SpaceGame::Initiliaze()
{
	m_font = std::make_shared<Font>("Minecraft.otf", 30);

	m_scoreText = std::make_shared<Text>(m_font);
	m_scoreText->Create(kiko::g_rend, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_shared<Text>(m_font);
	m_scoreText->Create(kiko::g_rend, "Asteroids", kiko::Color{ 1, 1, 1, 1 });
	//Load audio
	
	kiko::g_audSys.AddAudio("hit", "Laser_Shoot.wav");
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
		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}
		break;
	case kiko::SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::random(kiko::g_rend.GetHeight()),kiko::g_rend.GetWidth()}, 0, 6 }, kiko::g_modMan.Get("SpaceShip.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case kiko::SpaceGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;
		break;
	case kiko::SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}
	m_scoreText->Create(kiko::g_rend, "Score: " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void kiko::SpaceGame::Draw(Renderer& rend)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(rend, 400, 300);

	}
	m_scoreText->Draw(rend, 40, 40);
	m_scene->Draw(rend);
}
