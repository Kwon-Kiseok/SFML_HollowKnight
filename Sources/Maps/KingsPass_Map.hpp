#pragma once
#include "Map.hpp"
#include "../Objects/Moveable/Monster/Crawlid.hpp"
#include "../Objects/Moveable/Monster/Vengefly.hpp"

// 플레이어 레이어 5를 기준으로 잡음

using namespace sf;

class KingsPass_Map : public Map
{
private:
	Crawlid* crawlid;
	Crawlid* crawlid2;

	Vengefly* vengefly;
public:
	KingsPass_Map(Player* player_);
	virtual ~KingsPass_Map() {}
};

