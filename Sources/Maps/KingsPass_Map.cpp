#include "KingsPass_Map.hpp"
#include "../Objects/Stable/Portal.hpp"

KingsPass_Map::KingsPass_Map(Player* player_)
	: Map(player_)
{
	LoadMap("data_tables/maps/KingsPass_map_data.csv");

	maps_min_size = Vector2f(0.f, -1500.f);
	maps_max_size = Vector2f(6800.f, 1500.f);

	player->SetPosition(Vector2f(462.f, -569.f));
	// monster = new ~~
	crawlid = new Crawlid(1);
	crawlid2 = new Crawlid(-1);
	vengefly = new Vengefly(1);
	// monster.init();
	crawlid->SetPosition(Vector2f(3200.f, 1000.f));
	crawlid->Init();
	crawlid2->SetPosition(Vector2f(4600.f, 1000.f));
	crawlid2->Init();
	vengefly->SetPosition(Vector2f(4100.f, 520.f));
	vengefly->Init();
	//characters.push_back(monster);
	characters.push_back(crawlid);
	characters.push_back(crawlid2);
	characters.push_back(vengefly);

	// portal set
	kpToCR = new Portal();
	kpToCR->SetCurrMap(MAP_TYPE::KingsPass);
	kpToCR->SetNextMap(MAP_TYPE::CrossRoad, Vector2f(50.f, 300.f));
	kpToCR->SetType(PORTAL_TYPE::AUTO);
	kpToCR->SetPosition(Vector2f(6757.f, -316.f));

	portals.push_back(kpToCR);
}