#pragma once
#include "Map.hpp"
#include "../Objects/Moveable/Monster/Crawlid.hpp"
#include <vector>

using namespace sf;

class Town_Map : public Map
{
private:	
	Stable* object;
	// tempMob* monster;
	//
	Crawlid* crawlid;
	Crawlid* crawlid2;

public:
	Town_Map(Player* player_);
	virtual ~Town_Map() {}

};

