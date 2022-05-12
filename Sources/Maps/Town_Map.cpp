#include "Town_Map.hpp"
#include "../Objects/Stable/Portal.hpp"

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	LoadMap("data_tables/maps/Town_map_data.csv");
    
	// portal set
	townToKP = new Portal();
	townToKP->SetCurrMap(MAP_TYPE::Town);
	townToKP->SetNextMap(MAP_TYPE::KingsPass, Vector2f(500.f, -200.f));
	townToKP->SetPosition(Vector2f(2851.f, 885.f));

	townToCrossRoad = new Portal();
	townToCrossRoad->SetCurrMap(MAP_TYPE::Town);
	townToCrossRoad->SetNextMap(MAP_TYPE::CrossRoad, Vector2f(2500.f, 1900.f));
	townToCrossRoad->SetInteractable(false);
	townToCrossRoad->SetPosition(Vector2f(2265.f, 815.f));
	// 포지션 설정해주기
	// 부딪히는 상황에서 위쪽 키 입력받으면 interactable true로 바꿔주기

	portals.push_back(townToKP);
	portals.push_back(townToCrossRoad);

  // monster = new ~~
	crawlid = new Crawlid(1);
	crawlid2 = new Crawlid(1);
	vengefly = new Vengefly(1);
	// monster.init();
	crawlid->SetPosition(Vector2f(100.f, 700.f));
	crawlid->Init();
	crawlid2->SetPosition(Vector2f(600.f, 700.f));
	crawlid2->Init();
	vengefly->SetPosition(Vector2f(600.f, 500.f));
	vengefly->Init();
	//characters.push_back(monster);
	characters.push_back(crawlid);
	characters.push_back(crawlid2);
	characters.push_back(vengefly);
    
	player->SetPosition(Vector2f(200.f, 700.f));
}
