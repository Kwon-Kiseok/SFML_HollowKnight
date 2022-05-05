#pragma once
#include "../Character.hpp"

class Monster : public Character
{
protected:
	Vector2f startPos;
	Vector2f endPos;

public:
	Monster();
	virtual ~Monster();

	Vector2f GetStartPos();
	Vector2f GetEndPos();
};

