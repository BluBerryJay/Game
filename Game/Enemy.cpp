#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Framework/Scene.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;
	}

	kiko::Vector2 forward = kiko::Vector2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_rend.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_rend.GetWidth());

	// Add fire rate and timer

}

void Enemy::OnCollision(Actor* actor)
{

	if (actor->m_tag == "Player")
	{
		m_game->AddPoints(100);
		m_destroyed = true;
	}
	
}
