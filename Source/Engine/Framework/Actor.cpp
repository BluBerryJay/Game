#include "Actor.h"
#include "Renderer/Renderer.h"

void kiko::Actor::Update(float dt)
{
	if (m_lifespan != -1.0f)
	{
		m_lifespan -= dt;
		m_destroyed = (m_lifespan <= 0);
		
	}
}

void kiko::Actor::Draw(kiko::Renderer& renderer)
{
	m_model->Draw(renderer, m_transform);
}
