#include "MapManager.hpp"
#include "UIManager.hpp"
#include "../Maps/Town_Map.hpp"
#include "../Maps/KingsPass_Map.hpp"
#include "../Maps/CrossRoad_Map.hpp"
#include "../Maps/BossRoom_Map.hpp"
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

	// ���⼭ �ε� �� �����Ͱ� �ִ� ��Ȳ�̸�
	// �÷��̾� �ε� �������־�� ��
	startPos[MAP_TYPE::Town] = Vector2f(200.f, 815.f);
}

void MapManager::LoadMap(MAP_TYPE type)
{
	if (nullptr != map)
		map = nullptr;
	map = maps[type];
	map->Init();
	player->SetCurrentMap(type);
	// �ε��ϴ� �߿��� �浹ó���� ������Ʈ�� ���ƾ� ��
	// Ÿ�̹��� �ʹ� �̸�
	player->SetPosition(startPos[type]);

}

void MapManager::Update(float dt)
{
	if (UIManager::GetInstance().GetIsPause())
		return;
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Equal))
	{
		isDebugMode = !isDebugMode;
	}

	// �ǰ� �� �� ������Ʈ �ӵ� ��ü�� ����
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
