#pragma once
#include "Map.hpp"
#include "../Objects/Moveable/Monster/tempMob.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/Portal.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"

using namespace sf;

class Town_Map : public Map
{
private:
	tempMob* mob;
	Ground* grounds[30];
	Portal* portal;
	TownLayered* townBG_1;
	TownLayered* townBG_2;
	TownLayered* townBG_3;

public:
	Town_Map(Player* player_);
	~Town_Map() {}

	void InitTownBG();
};

