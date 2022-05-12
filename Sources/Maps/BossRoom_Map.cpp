#include "BossRoom_Map.hpp"
#include "../Objects/Stable/Portal.hpp"

BossRoom_Map::BossRoom_Map(Player* player_)
	: Map(player_)
{
	LoadMap("data_tables/maps/BossRoom_map_data.csv");

	//
	brToTown = new Portal();
	brToTown->SetCurrMap(MAP_TYPE::BossRoom);
	brToTown->SetNextMap(MAP_TYPE::Town, Vector2f(1077.f, 815.f));
	brToTown->SetInteractable(false);
	brToTown->SetPosition(Vector2f(3055.f, -345.f));

	portals.push_back(brToTown);
}
