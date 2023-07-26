#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Game.h"
#include "../Input/InputSystem.h"
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
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_rend.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_rend.GetWidth());

	// Fire weapon
	if (kiko::g_inSys.GetKeyDown(SDL_SCANCODE_SPACE)) {
		kiko::Transform trans{ m_transform.position, m_transform.rotation, m_transform.scale };
		std::unique_ptr<Weapon> weapon = make_unique<Weapon>(300.0f, trans, m_model);
		weapon->m_tag = "Player";
		m_scene->Add(std::move(weapon));


	}
}

void Player::OnCollision(Actor* actor)
{
	if (actor->m_tag == "Enemy" && m_playerHealth <= 0)
	{
		m_game->SetLives(m_game->GetLives() - 1);
		dynamic_cast<kiko::SpaceGame*>(m_game)->SetState(kiko::SpaceGame::eState::PlayerDead);

		m_destroyed = true;
	}
	else if (actor->m_tag == "Enemy") {
		m_playerHealth -= 2.5;
	}
	
}

//void Player::Draw(kiko::Renderer& renderer)
//{
//
//}
