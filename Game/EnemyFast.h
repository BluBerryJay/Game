#pragma once
#include "Framework/Actor.h"
#include "Renderer/Renderer.h"
class EnemyFast : public kiko::Actor
{
public:
	EnemyFast(float speed, float turnRate, const kiko::Transform& transform, const std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}
	kiko::Vector2 GetPosition() {
		return m_transform.position;

	}
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;


protected:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};