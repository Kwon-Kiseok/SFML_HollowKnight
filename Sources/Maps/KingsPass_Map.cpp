#include "KingsPass_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Player/Player.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/Portal.hpp"

#include <iostream>

KingsPass_Map::KingsPass_Map(Player* player_)
	: Map(player_)
{
	portal = new Portal();

	float groundsLength = 0.f;
	for (int i = 0; i < 30; ++i)
	{
		grounds[i] = new Ground();
		if (i == 0)
		{
			grounds[i]->SetPosition(0.f, 820.f);
		}
		else
		{
			grounds[i]->SetPosition(groundsLength + (grounds[i - 1]->GetSprite().getLocalBounds().width), 820.f);
			groundsLength += grounds[i - 1]->GetSprite().getLocalBounds().width - 4.f;
		}
		grounds[i]->GetSprite().setPosition(grounds[i]->GetPosition());
	}

	portal->SetPosition(0.f, 820.f);
	portal->GetSprite().setPosition(portal->GetPosition());
	portal->SetNextMap(MAP_TYPE::Town);

	this->player->SetPosition(Vector2f(300.f / 2, 500.f));
	//player->Init();
	gameObjects.push_back(player);

	for (int i = 0; i < 30; ++i)
	{
		stableObjects.push_back(grounds[i]);
	}
	stableObjects.push_back(portal);
}