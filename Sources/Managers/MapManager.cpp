#include "MapManager.hpp"
#include "UIManager.hpp"
#include "../Maps/Town_Map.hpp"
#include "../Maps/KingsPass_Map.hpp"
#include "../Maps/CrossRoad_Map.hpp"
#include "../Maps/BossRoom_Map.hpp"
#include "SoundManager.hpp"
#include <iostream>

MapManager::~MapManager() noexcept
{
	delete player;
	player = nullptr;

	map = nullptr;
	Release();
}

void MapManager::Init()
{
	player = new Player();
	std::cout << "player create" << std::endl;
	player->Init();
	
	maps[MAP_TYPE::Town] = new Town_Map(player);
	maps[MAP_TYPE::KingsPass] = new KingsPass_Map(player);
	maps[MAP_TYPE::CrossRoad] = new CrossRoad_Map(player);
	maps[MAP_TYPE::BossRoom] = new BossRoom_Map(player);

	// 여기서 로드 된 데이터가 있는 상황이면
	// 플레이어 로드 셋팅해주어야 함
	startPos[MAP_TYPE::Town] = Vector2f(200.f, 815.f);
}

void MapManager::LoadMap(MAP_TYPE type)
{
	if (nullptr != map)
		map = nullptr;

	SoundManager::GetInstance().StopMusic();
	map = maps[type];
	map->Init();
	player->SetCurrentMap(type);
	// 로드하는 중에는 충돌처리나 업데이트를 막아야 함
	// 타이밍이 너무 이름
	player->SetPosition(startPos[type]);
	switch (type)
	{
	case MAP_TYPE::Town:
		SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/Dirtmouth 1.wav");
		break;
	case MAP_TYPE::KingsPass:
		SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/RESTING GROUNDS S51-14.wav");
		break;
	case MAP_TYPE::CrossRoad:
		SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/S19 Crossroads Bass.wav");
		break;
	case MAP_TYPE::BossRoom:
		SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/S61-216 Hollow Knight.wav");
		break;
	}
}

void MapManager::Update(float dt)
{
	if (UIManager::GetInstance().GetIsPause())
		return;
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Equal))
	{
		isDebugMode = !isDebugMode;
	}

	// 피격 시 맵 업데이트 속도 자체를 늦춤
	if (player->GetPlayerAnimController().IsPlaying("Stun"))
	{
		dt = player->SlowDT(dt);
	}

	map->Update(dt);
	map->CheckCollisions(dt);
}

void MapManager::Render(sf::RenderWindow& window)
{
	map->Render(window);
}

void MapManager::Release()
{
	for (auto& map : maps)
	{
		map.second->Release();

		delete map.second;
	}
	maps.clear();
}

Map* MapManager::GetCurrentMap()
{
	return map;
}

void MapManager::SetStartPos(MAP_TYPE type, sf::Vector2f pos)
{
	startPos[type] = pos;
}

bool MapManager::GetIsDebugMode()
{
	return isDebugMode;
}
