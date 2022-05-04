#include "MapManager.hpp"
#include "../Maps/Town_Map.hpp"
#include "../Maps/KingsPass_Map.hpp"
#include "../Maps/CrossRoad_Map.hpp"

#include <iostream>

MapManager::~MapManager() noexcept
{
}

void MapManager::Init()
{
}

void MapManager::LoadMap(MAP_TYPE type)
{
	Release();

	switch (type)
	{
	case MAP_TYPE::Town:
		map = new Town_Map();
		break;
	case MAP_TYPE::KingsPass:
		map = new KingsPass_Map();
		break;
	case MAP_TYPE::CrossRoad:
		map = new CrossRoad_Map();
		break;
	default:
		break;
	}
	map->Init();
	std::cout << static_cast<int>(type) << std::endl;
}

void MapManager::Update(float dt)
{
	map->Update(dt);
}

void MapManager::Render(sf::RenderWindow& window)
{
	map->Render(window);
}

void MapManager::Release()
{
	if (map != nullptr)
	{
		map->Release();
		delete map;
		map = nullptr;
	}
}

Map* MapManager::GetCurrentMap()
{
	return map;
}
