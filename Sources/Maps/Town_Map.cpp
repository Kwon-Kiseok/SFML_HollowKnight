#include "Town_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Player/Player.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include <iostream>

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	mob = new tempMob();
	ground_1 = new Ground();
	ground_2 = new Ground();
	portal = new Portal();

	ground_1->SetPosition(990.f, 820.f);
	ground_1->SetOriginCenter();
	ground_1->GetSprite().setPosition(ground_1->GetPosition());

	ground_2->SetPosition(1300.f, 820.f);
	ground_2->SetOriginCenter();
	ground_2->GetSprite().setPosition(ground_2->GetPosition());

	portal->SetPosition(1600.f, 820.f);

	this->player->SetPosition(Vector2f(1920.f / 2, 500.f));
	this->player->Init();
	mob->Init();
	mob->SetPosition(Vector2f(1920.f / 2.f, 850.f));
	gameObjects.push_back(this->player);
	gameObjects.push_back(mob);

	stableObjects.push_back(ground_1);
	stableObjects.push_back(ground_2);
	stableObjects.push_back(portal);
}