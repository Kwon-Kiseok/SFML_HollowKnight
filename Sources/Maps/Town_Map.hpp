#pragma once
#include "Map.hpp"
#include "../Objects/Moveable/Monster/tempMob.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/Portal.hpp"

using namespace sf;

class Town_Map : public Map
{
private:
	tempMob* mob;
	Ground* grounds[30];
	Portal* portal;
public:
	Town_Map(Player* player_);
	~Town_Map() {}
};

