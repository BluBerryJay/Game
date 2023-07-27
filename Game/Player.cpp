#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Game.h"
#include "../Input/InputSystem.h"
#include "Renderer/ModelManager.h"
#include "../Audio/AudioSystem.h"
#include "Weapon.h"
#include "Framework/Scene.h"

void Player::Update(float dt)
{
	float rotate = 0;
	if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();



	float thrust = 0;
	if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::Vector2 forward = kiko::Vector2{ 0,-1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();

	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_rend.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_rend.GetWidth());

	// Fire weapon
	if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inSys.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		kiko::Transform trans1{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), m_transform.scale };
		kiko::Transform trans2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(10.0f), m_transform.scale };
		std::unique_ptr<Weapon> weapon = make_unique<Weapon>(300.0f, trans1, kiko::g_modMan.Get("Laser.txt"));
		weapon->m_tag = "Laser";
		m_scene->Add(std::move(weapon));
		

		weapon = make_unique<Weapon>(300.0f, trans2, kiko::g_modMan.Get("Laser.txt"));
		weapon->m_tag = "Laser";
		m_scene->Add(std::move(weapon));
		kiko::g_audSys.PlayOneShot("hit", false);
		
	}
	if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_T)) { kiko::g_time.SetTimeScale(0.5f); }
	else kiko::g_time.SetTimeScale(1.0f);
	
	
}

void Player::OnCollision(Actor* actor)
{
	if (actor->m_tag == "Enemy" && m_game->GetLives() > 0)
	{
		m_game->SetLives(m_game->GetLives() - 1);
	}
	if (actor->m_tag == "Enemy" && m_game->GetLives() == 0)
	{
		//m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
		dynamic_cast<kiko::SpaceGame*>(m_game)->SetState(kiko::SpaceGame::eState::PlayerDeadStart);

	}
	
	
}


