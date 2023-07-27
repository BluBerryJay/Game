#include "EnemyFast.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Framework/Scene.h"

void EnemyFast::Update(float dt)
{
	Actor::Update(dt);
	kiko::Vector2 forward = kiko::Vector2{ 0,-1 }.Rotate(m_transform.rotation);
	kiko::Vector2 equate;
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		float turnAngle = equate.SignedAngle(forward, direction.Normalized());




		m_transform.rotation += turnAngle * 5 * dt;

		float angle = equate.Angle(forward, direction.Normalized());
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{

		}
	}

	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_rend.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_rend.GetWidth());

	// Add fire rate and timer

}

void EnemyFast::OnCollision(Actor* actor)
{

	if (actor->m_tag == "Laser")
	{
		m_game->AddPoints(150);
		m_destroyed = true;
	}
	if (actor->m_tag == "Player")
	{
		m_destroyed = true;
	}
	
}
