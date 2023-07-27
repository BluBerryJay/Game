#pragma once
#include "Framework/Actor.h"

class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, const kiko::Transform& transform, const std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }

	{
		m_lifespan = 2.0f;
	}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
	kiko::Vector2 GetPosition() {
		return m_transform.position;

	}

protected:
	float m_speed = 0;
};