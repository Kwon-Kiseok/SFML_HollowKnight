#include "PlayScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/UIManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Managers/PlayerDataManager.hpp"

PlayScene::PlayScene()
{
}

void PlayScene::Init()
{
	MapManager::GetInstance().Init();
	MapManager::GetInstance().LoadMap(MAP_TYPE::BossRoom);
	UIManager::GetInstance().Init_PlayScene();
}

void PlayScene::Update(float dt)
{
	MapManager::GetInstance().Update(dt);
	UIManager::GetInstance().Update_PlayScene(dt);
}

void PlayScene::Render(sf::RenderWindow& window)
{
	MapManager::GetInstance().Render(window);
	UIManager::GetInstance().Render_PlayScene(window);
}

void PlayScene::Release()
{
	MapManager::GetInstance().Release();
}
