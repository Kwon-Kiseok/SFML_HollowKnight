#pragma once
#include "../Character.hpp"
#include "../../../Items/Coin.hpp"

class Monster : public Character
{
protected:
	Vector2f startPos;
	Vector2f endPos;

	Coin* coin;

public:
	Monster();
	virtual ~Monster();

	Vector2f GetStartPos();
	Vector2f GetEndPos();


};

