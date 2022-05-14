#pragma once
#include "Map.hpp"
#include "../../Sources/Objects/Moveable/Monster/FalseKnight.hpp"

class Portal;
class BossRoom_Map : public Map
{
private:
	Portal* brToTown;

	FalseKnight* boss;
public:
	BossRoom_Map(Player* player_);
	virtual ~BossRoom_Map() {}
};

