#pragma once
#include "Stable.hpp"

class Bench : public Stable
{
public:
	Bench();
	virtual ~Bench();
	
	virtual void Interaction() override;
	virtual void Render(RenderWindow& window) override;
	virtual bool Collision(GameObject* otherObj) override;
};

