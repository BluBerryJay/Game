#pragma once

#include "Framework/Actor.h"


class Player : public kiko::Actor 
{
public:
	Player(float health, float speed, float turnRate, const kiko::Transform& transform, const std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_playerHealth{ health },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_playerHealth = 0;
};