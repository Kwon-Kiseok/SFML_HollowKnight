#pragma once
#include "Map.hpp"

using namespace sf;

class Ground;
class Portal;
class KingsPass_Map : public Map
{
private:
	Ground* grounds[30];
	Portal* portal;
public:
	KingsPass_Map(Player* player_);
	virtual ~KingsPass_Map() {}
};

