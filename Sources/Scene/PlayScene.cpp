#include "PlayScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"

void PlayScene::Init()
{
	player = new Player();
	player->Init();
	tile = new DemoTile(740, 900);
}

void PlayScene::Update(float dt)
{
	player->Update(dt, tile->GetGlobalBounds());
}

void PlayScene::Render(sf::RenderWindow& window)
{
	player->Draw(window);
	window.draw(tile->GetShape());
}

void PlayScene::Release()
{
	delete player;
	delete tile;
}
