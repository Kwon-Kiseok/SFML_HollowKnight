#include "Town_Map.hpp"

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	LoadMap("data_tables/maps/Town_map_data.csv");
    
  // monster = new ~~
	crawlid = new Crawlid(1);
	crawlid2 = new Crawlid(1);
	vengefly = new Vengefly(1);
	// monster.init();
	crawlid->SetPosition(Vector2f(100.f, 850.f));
	crawlid->Init();
	crawlid2->SetPosition(Vector2f(600.f, 850.f));
	crawlid2->Init();
	vengefly->SetPosition(Vector2f(600.f, 500.f));
	vengefly->Init();
	//characters.push_back(monster);
	characters.push_back(crawlid);
	characters.push_back(crawlid2);
	characters.push_back(vengefly);
    
	player->SetPosition(Vector2f(200.f, 700.f));
}
