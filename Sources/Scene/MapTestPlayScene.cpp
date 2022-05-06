#include "MapTestPlayScene.hpp"
#include "../Managers/MapManager.hpp"
#include "../Managers/InputManager.hpp"

MapTestPlayScene::MapTestPlayScene()
{
}

MapTestPlayScene::~MapTestPlayScene() noexcept
{
}

void MapTestPlayScene::Init()
{
	MapManager::GetInstance().Init();
	MapManager::GetInstance().LoadMap(MAP_TYPE::Town);
}

void MapTestPlayScene::Update(float dt)
{
	MapManager::GetInstance().Update(dt);	
}

void MapTestPlayScene::Render(sf::RenderWindow& window)
{
	MapManager::GetInstance().Render(window);
}

void MapTestPlayScene::Release()
{
	MapManager::GetInstance().Release();
}
