#pragma once
#include "Map.hpp"
#include <vector>
#include "../../Sources/Objects/Moveable/Monster/FalseKnight.hpp"

using namespace sf;

class Portal;
class Town_Map : public Map
{
private:	
	Stable* object;

	Portal* townToKP;
	Portal* townToCrossRoad;

	FalseKnight* boss;
public:
	Town_Map(Player* player_);
	virtual ~Town_Map() {}
};

