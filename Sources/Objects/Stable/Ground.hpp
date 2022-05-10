#pragma once
#include "Stable.hpp"

class Ground : public Stable
{
public:
	Ground();
	Ground(int idx);
	virtual ~Ground();

	virtual bool Collision(GameObject* otherObj) override;
};

class KingsPassGround : public Stable
{
public:
	KingsPassGround();
	KingsPassGround(int idx);
	virtual ~KingsPassGround();
};