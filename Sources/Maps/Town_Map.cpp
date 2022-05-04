#include "Town_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Player/Player.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/PlayerDataManager.hpp"

#include <iostream>

Town_Map::Town_Map()
{
}

void Town_Map::Init()
{
	textureBG.loadFromFile("Resources/Sprite/BG/Town/town_bench.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setPosition(990.f, 820.f);
	spriteBG.setOrigin(spriteBG.getLocalBounds().width / 2, spriteBG.getLocalBounds().height / 2);

	texturePortal.loadFromFile("Resources/Sprite/BG/Tutorial/tut_door_large_0007_04.png");
	spritePortal.setTexture(texturePortal);
	spritePortal.setPosition(2500.f, 820.f);
	spritePortal.setOrigin(spritePortal.getLocalBounds().width / 2, spritePortal.getLocalBounds().height / 2);

	player = new Player();
	mob = new tempMob();
	tile = new DemoTile(740, 900);
	player->Init();
	mob->Init();
	mob->SetPosition(Vector2f(1920.f / 2.f, 850.f));
}

void Town_Map::Update(float dt)
{
	player->Update(dt, tile->GetGlobalBounds());
	mob->Update(dt);

	ViewManager::GetInstance().GetMainView().setCenter(player->GetPosition());

	if (spritePortal.getGlobalBounds().intersects(player->GetGlobalBounds()))
	{
		player->AddHP(1000);
		PlayerDataManager::GetInstance().SavePlayerData(*player);
		MapManager::GetInstance().LoadMap(MAP_TYPE::KingsPass);
	}

}

void Town_Map::Render(RenderWindow& window)
{
	window.draw(spriteBG);
	window.draw(spritePortal);
	window.draw(tile->GetShape());
	player->Draw(window);
	mob->Render(window);
}

void Town_Map::Release()
{
	delete player;
	delete tile;
	player = nullptr;
	tile = nullptr;
}
