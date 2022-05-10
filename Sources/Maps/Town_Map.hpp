#pragma once
#include "Map.hpp"
#include "../Objects/Moveable/Monster/Crawlid.hpp"
#include <vector>

using namespace sf;
using namespace std;

class Stable;
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
	~Town_Map() {}

	void LoadMap();
	void AddObject(MapData& data);
};

