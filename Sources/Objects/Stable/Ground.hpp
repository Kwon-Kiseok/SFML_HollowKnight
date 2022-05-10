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

class CrossRoadGround : public Stable
{
public:
	CrossRoadGround() { index_total = 13; };
	CrossRoadGround(int idx);
	virtual ~CrossRoadGround() {};
};