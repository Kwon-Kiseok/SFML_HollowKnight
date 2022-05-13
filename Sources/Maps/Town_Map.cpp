#include "Town_Map.hpp"
#include "../Objects/Stable/Portal.hpp"

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	LoadMap("data_tables/maps/Town_map_data.csv");
    
	maps_min_size = Vector2f(0.f, 0.f);
	maps_max_size = Vector2f(3000.f, 1000.f);

	/*******************************
	* 보스 테스트
	********************************/
	boss = new FalseKnight();
	// monster.init();
	boss->SetPosition(Vector2f(2265.f, 815.f));
	boss->Init();
	characters.push_back(boss);
	//characters.push_back(monster);

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

	player->SetPosition(Vector2f(200.f, 700.f));
}
