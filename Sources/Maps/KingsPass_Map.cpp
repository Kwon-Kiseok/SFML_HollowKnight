#include "KingsPass_Map.hpp"
#include "../Objects/Stable/Portal.hpp"

KingsPass_Map::KingsPass_Map(Player* player_)
	: Map(player_)
{
	LoadMap("data_tables/maps/KingsPass_map_data.csv");

	// portal set
	kpToCR = new Portal();
	kpToCR->SetCurrMap(MAP_TYPE::KingsPass);
	kpToCR->SetNextMap(MAP_TYPE::CrossRoad, Vector2f(50.f, 300.f));
	// Æ÷Áö¼Ç
	kpToCR->SetPosition(Vector2f(6757.f, -316.f));

	portals.push_back(kpToCR);
}