#pragma once
#include "../Character.hpp"
#include "../../../Items/Coin.hpp"
#include "../../../Managers/PlayerDataManager.hpp"

class Monster : public Character
{
protected:
	Vector2f startPos;
	Vector2f endPos;

	int coin;					//������ ���η�

public:
	Monster();
	virtual ~Monster();

	Vector2f GetStartPos();
	Vector2f GetEndPos();


};

