#include "CrossRoad_Map.hpp"
#include "../Objects/Stable/Portal.hpp"

CrossRoad_Map::CrossRoad_Map(Player* player_)
	: Map(player_)
{
	LoadMap("data_tables/maps/CrossRoad_map_data.csv");

	//
	crToBR = new Portal();
	crToBR->SetCurrMap(MAP_TYPE::CrossRoad);
	crToBR->SetNextMap(MAP_TYPE::BossRoom, Vector2f(-50.f, 740.f));
	crToBR->SetInteractable(false);
	crToBR->SetPosition(Vector2f(4672.f, 2223.f));

	crToTown = new Portal();
	crToTown->SetCurrMap(MAP_TYPE::CrossRoad);
	crToTown->SetNextMap(MAP_TYPE::Town, Vector2f(2265.f, 815.f));
	crToTown->SetInteractable(false);
	crToTown->SetPosition(Vector2f(2500.f, 1900.f));

	portals.push_back(crToBR);
	portals.push_back(crToTown);
}