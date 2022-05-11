#include "Town_Map.hpp"

Town_Map::Town_Map(Player* player)
	: Map(player)
{

	LoadMap("data_tables/maps/Town_map_data.csv");
    
  // monster = new ~~
	crawlid = new Crawlid(1);
	crawlid2 = new Crawlid(1);
	// monster.init();
	crawlid->SetPosition(Vector2f(100.f, 800.f));
	crawlid->Init();
	crawlid2->SetPosition(Vector2f(600.f, 800.f));
	crawlid2->Init();
	//characters.push_back(monster);
	characters.push_back(crawlid);
	characters.push_back(crawlid2);
    
	player->SetPosition(Vector2f(200.f, 800.f));
}