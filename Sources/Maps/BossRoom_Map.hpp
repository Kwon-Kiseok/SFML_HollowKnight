#pragma once
#include "Map.hpp"

class Portal;
class BossRoom_Map : public Map
{
private:
	Portal* brToTown;
public:
	BossRoom_Map(Player* player_);
	virtual ~BossRoom_Map() {}
};

