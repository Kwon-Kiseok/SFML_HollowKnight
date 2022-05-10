#include "Town_Map.hpp"

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	LoadMap("data_tables/maps/Town_map_data.csv");
	player->SetPosition(Vector2f(550.f, 845.f));
}