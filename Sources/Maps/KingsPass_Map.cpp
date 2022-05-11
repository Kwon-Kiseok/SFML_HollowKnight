#include "KingsPass_Map.hpp"

KingsPass_Map::KingsPass_Map(Player* player_)
	: Map(player_)
{
	LoadMap("data_tables/maps/KingsPass_map_data.csv");
	player->SetPosition(Vector2f(462.f, -569.f));

}