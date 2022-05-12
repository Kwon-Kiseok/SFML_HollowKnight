#include "Town_Map.hpp"

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	LoadMap("data_tables/maps/Town_map_data.csv");    
	player->SetPosition(Vector2f(200.f, 700.f));
}
