#pragma once
#include "Stable.hpp"

class Collider;
class Bench : public Stable
{
private:
	Collider* collider;
public:
	Bench();
	virtual ~Bench();
	
	virtual void Interaction(Player& player) override;
	virtual void Render(RenderWindow& window) override;
	virtual bool Collision(GameObject* otherObj) override;
};

