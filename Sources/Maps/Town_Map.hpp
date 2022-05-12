#pragma once
#include "Map.hpp"
#include <vector>

using namespace sf;

class Town_Map : public Map
{
private:	
	Stable* object;
	// tempMob* monster;
	//
	
public:
	Town_Map(Player* player_);
	virtual ~Town_Map() {}

};

