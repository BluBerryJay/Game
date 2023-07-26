#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
void Weapon::Update(float dt)
{
	Actor::Update(dt);

	kiko::Vector2 forward = kiko::Vector2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_rend.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_rend.GetWidth());

}

void Weapon::OnCollision(Actor* actor)
{
	if (actor->m_tag != m_tag)
	{
		m_destroyed = true;
	}
	
}
