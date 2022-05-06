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
	portal = new Portal();

	InitTownBG();

	float groundsLength = 0.f;
	for (int i = 0; i < 30; ++i)
	{
		grounds[i] = new Ground(1);
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
		grounds[i]->SetLayer(0);
	}

	portal->SetPosition(10350.f, 820.f);
	portal->GetSprite().setPosition(portal->GetPosition());
	portal->SetNextMap(MAP_TYPE::KingsPass);

	this->player->SetPosition(Vector2f(1920.f / 2, 500.f));
	mob->Init();
	mob->SetPosition(Vector2f(1920.f / 2.f, 850.f));
	characters.push_back(this->player);
	characters.push_back(mob);

	for (int i = 0; i < 30; ++i)
	{
		stableObjects.push_back(grounds[i]);
	}
	stableObjects.push_back(portal);
	stableObjects.push_back(townBG_1);
	stableObjects.push_back(townBG_2);
	stableObjects.push_back(townBG_3);
}

void Town_Map::InitTownBG()
{
	townBG_1 = new TownLayered(0);
	townBG_2 = new TownLayered(0);
	townBG_3 = new TownLayered(0);

	townBG_1->SetTexture("Resources/Sprite/BG/town/town_layered_0002_35.png");
	townBG_1->SetSprite();
	townBG_1->SetLayer(2);
	townBG_1->GetSprite().setScale(10.f, 10.f);
	townBG_1->SetPosition(0.f, -300.f);

	townBG_2->SetTexture("Resources/Sprite/BG/town/town_layered_0004_33.png");
	townBG_2->SetSprite();
	townBG_2->SetLayer(3);
	townBG_2->GetSprite().setScale(10.f, 10.f);
	townBG_2->SetPosition(700.f, -300.f);

	townBG_3->SetTexture("Resources/Sprite/BG/town/town_layered_0000_37.png");
	townBG_3->SetSprite();
	townBG_3->SetLayer(1);
	townBG_3->GetSprite().setScale(6.f, 6.f);
	townBG_3->SetPosition(-100.f, 450.f);
}
