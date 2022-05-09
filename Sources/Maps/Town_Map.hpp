#pragma once
#include "Map.hpp"
#include "../Objects/Moveable/Monster/tempMob.hpp"
#include <vector>

using namespace sf;
using namespace std;

class Stable;
class Town_Map : public Map
{
private:	
	Stable* object;

public:
	Town_Map(Player* player_);
	~Town_Map() {}

	void LoadMap();
	void AddObject(MapData& data);
};

