#pragma once
#include "Map.hpp"

class Portal;
class CrossRoad_Map : public Map
{
private:
	Portal* crToBR;
	Portal* crToTown;
public:
	CrossRoad_Map(Player* player_);
	virtual ~CrossRoad_Map() {}
};

