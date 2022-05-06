#pragma once
#include "Stable.hpp"

class Ground : public Stable
{
private:

public:
	Ground();
	virtual ~Ground();

	virtual bool Collision(GameObject* otherObj) override;
};

