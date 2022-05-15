#include "BossRoom_Map.hpp"
#include "../Objects/Stable/Portal.hpp"
#include "../Objects/Stable/Platform.hpp"

BossRoom_Map::BossRoom_Map(Player* player_)
	: Map(player_)
{
	LoadMap("data_tables/maps/BossRoom_map_data.csv");

	maps_min_size = Vector2f(-250.f, -600.f);
	maps_max_size = Vector2f(4000.f, 1000.f);

	/*******************************
	* 보스 테스트
	********************************/
	boss = new FalseKnight();
	// monster.init();
	boss->SetPosition(Vector2f(1077.f, 515.f));
	boss->Init();
	characters.push_back(boss);
	//characters.push_back(monster);
	//
	brToTown = new Portal();
	brToTown->SetCurrMap(MAP_TYPE::BossRoom);
	brToTown->SetNextMap(MAP_TYPE::Town, Vector2f(1077.f, 815.f));
	brToTown->SetInteractable(false);
	brToTown->SetType(PORTAL_TYPE::MANUAL);
	brToTown->SetPosition(Vector2f(3055.f, -345.f));

	portals.push_back(brToTown);

	elevator = new Platform(11);
	elevator->SetInteractable(false);
	elevator->SetPosition(Vector2f(3609.f, 760.f));
	elevator->SetOriginCenter();
	elevator->SetElevator(-265.f, -1, 150.f);
	stableObjects.push_back(elevator);
	colliders.push_back(elevator->GetCollider());
}
