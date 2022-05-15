#pragma once
#include "Map.hpp"
#include "../../Sources/Objects/Moveable/Monster/FalseKnight.hpp"

class Portal;
class Platform;
class BossRoom_Map : public Map
{
private:
	Portal* brToTown;
	Platform* elevator;
	FalseKnight* boss;
public:
	BossRoom_Map(Player* player_);
	virtual ~BossRoom_Map() {}
};

