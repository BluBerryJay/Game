#include "Heart.h"
#include "Framework/Game.h"
void Heart::Update(float dt)
{
	Actor::Update(dt);
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_rend.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_rend.GetWidth());
}

void Heart::OnCollision(Actor* actor)
{
	if (actor->m_tag == "Player")
	{
		m_game->SetLives(m_game->GetLives() + 1);
		m_destroyed = true;
	}
}
