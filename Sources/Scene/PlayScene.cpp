#include "PlayScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/UIManager.hpp"

void PlayScene::Init()
{
	player = new Player();
	player->Init();
	tile = new DemoTile(740, 900);
	UIManager::GetInstance().Init_PlayScene();
}

void PlayScene::Update(float dt)
{
	if(!UIManager::GetInstance().GetInventoryIsOpen())
		player->Update(dt, tile->GetGlobalBounds());
	UIManager::GetInstance().Update_PlayScene(dt);
}

void PlayScene::Render(sf::RenderWindow& window)
{
	player->Draw(window);
	window.draw(tile->GetShape());
	UIManager::GetInstance().Render_PlayScene(window);
}

void PlayScene::Release()
{
	delete player;
	delete tile;
}
