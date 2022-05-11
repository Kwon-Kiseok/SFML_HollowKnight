#pragma once
#include "Map.hpp"

// 플레이어 레이어 5를 기준으로 잡음

using namespace sf;

class KingsPass_Map : public Map
{
private:

public:
	KingsPass_Map(Player* player_);
	virtual ~KingsPass_Map() {}
};

