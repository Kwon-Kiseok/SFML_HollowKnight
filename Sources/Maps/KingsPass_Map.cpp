#include "KingsPass_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Player/Player.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/PlayerDataManager.hpp"

#include <iostream>

void KingsPass_Map::Init()
{
	textureBG.loadFromFile("Resources/Sprite/BG/Tutorial/tut_tab_ancient_0001_2.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setPosition(990.f, 820.f);
	spriteBG.setOrigin(spriteBG.getLocalBounds().width / 2, spriteBG.getLocalBounds().height / 2);

	player = new Player();
	tile = new DemoTile(740, 900);
	player->Init();

	std::cout << player->GetHP() << std::endl;
}

void KingsPass_Map::Update(float dt)
{
	player->Update(dt, tile->GetGlobalBounds());
	ViewManager::GetInstance().GetMainView().setCenter(player->GetPosition());

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Space))
	{
		MapManager::GetInstance().LoadMap(MAP_TYPE::CrossRoad);
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::BackSpace))
	{
		MapManager::GetInstance().LoadMap(MAP_TYPE::Town);
	}
}

void KingsPass_Map::Render(sf::RenderWindow& window)
{
	window.draw(spriteBG);
	window.draw(tile->GetShape());
	player->Draw(window);
}

void KingsPass_Map::Release()
{
	delete player;
	delete tile;
	player = nullptr;
	tile = nullptr;
}
