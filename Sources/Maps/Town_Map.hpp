#pragma once
#include "Map.hpp"
#include <vector>

using namespace sf;

class Portal;
class Town_Map : public Map
{
private:	
	Stable* object;

	Portal* townToKP;
	Portal* townToCrossRoad;

public:
	Town_Map(Player* player_);
	virtual ~Town_Map() {}
};

