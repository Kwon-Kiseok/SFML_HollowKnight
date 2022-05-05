#include "KingsPass_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Player/Player.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../DemoTile.hpp"

#include <iostream>

KingsPass_Map::KingsPass_Map(Player* player_)
	: Map(player_)
{
	this->player->SetPosition(Vector2f(1920.f / 2, 500.f));
	//player->Init();
	gameObjects.push_back(player);
}