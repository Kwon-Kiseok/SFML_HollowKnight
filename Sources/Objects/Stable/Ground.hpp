#pragma once
#include "Stable.hpp"

class Ground : public Stable
{
public:
	Ground();
	Ground(int idx);
	virtual ~Ground();

	void SetImageIdx(int idx);
	virtual bool Collision(GameObject* otherObj) override;
};

