#pragma once
#include "Framework/Actor.h"

class Heart : public kiko::Actor
{
public:
	
	Heart(const kiko::Transform& trans, std::shared_ptr<kiko::Model> model) :
		Actor{ trans, model }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
protected:

};
