#pragma once
#include "Stable.hpp"

class thorn : public Stable
{
private:
	Vector2f moveToPos;
public:
	thorn();
	virtual ~thorn();

	virtual void Interaction(Player& player) override;
};

