#include "Map.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Objects/Stable/Stable.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/bench.hpp"
#include "../Objects/Stable/Portal.hpp"
#include "../Objects/Stable/Wall.hpp"

#include "../Objects/Stable/Door.hpp"
#include "../Objects/Stable/KingsPassImages.hpp"
#include "../Objects/Stable/Platform.hpp"
#include "../Objects/Stable/thorn.hpp"

#include <iostream>

void Map::Init()
{
	characters.push_back(player);
}

void Map::Update(float dt)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update(dt);
	}

	for (auto it = characters.begin(); it != characters.end(); ++it)
	{
		(*it)->Update(dt);
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::P))
	{
		std::cout << "Player's X: " << player->GetPosition().x << " Y: " << player->GetPosition().y << std::endl;
	}

	ViewManager::GetInstance().GetMainView().setCenter(player->GetPosition());
}

void Map::Render(sf::RenderWindow& window)
{

	for (int i = 10; i >= 0; --i)
	{
		for (auto it = stableObjects.begin(); it != stableObjects.end(); ++it)
		{
			if ((*it)->GetLayer() == i)
			{
				(*it)->Render(window);
			}

			window.draw((*it)->GetRectangleShape());
		}
	}

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Render(window);
	}

	for (auto it = characters.begin(); it != characters.end(); ++it)
	{
		(*it)->Render(window);
	}

	for (auto it = portals.begin(); it != portals.end(); ++it)
	{
		(*it)->Render(window);
	}

}

void Map::Release()
{
	for (auto it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}
	stableObjects.clear();

	for (auto it = portals.begin(); it != portals.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}
	portals.clear();

}

void Map::CheckCollisions(float dt)
{
	Vector2f positionTemp = player->GetPosition();
	for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			player->Collision(*it);

			if ((*it)->CompareTag(TAG::MONSTER))
			{
				std::cout << player->GetName() << " Collision Monster" << std::endl;
			}
		}
	}

	for (std::vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			player->Collision(*it);

			// �÷��̾�� ���Ͱ� �浹���� ���
			if ((*it)->CompareTag(TAG::MONSTER))
			{
				std::cout << player->GetName() << " Collision Monster" << std::endl;
				//player->OnHitted(dt);
			}
		}
		/******************************************
		* ���Ͱ� �÷��̾��� ���ݹڽ��� �ε����� ���
		* �̰� �³���????
		******************************************/
		RectangleShape attackBox = player->GetAttackBox();
		if ((*it)->Collision_AttackBox(attackBox) && (*it)->CompareTag(TAG::MONSTER))
		{
			player->UpdateCollision();
		}

		//if (player->Collision_AttackBox((*it)->GetAttackBox()) && (*it)->CompareTag(TAG::MONSTER))
		//{
		//	// �÷��̾ ������ ���ùڽ��� ���ߴ����� ��
		//  // �÷��̾� �˹� + ������ ����
		//}
	}

	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			// ���� �ε����� ��
			if ((*it)->CompareTag(TAG::GROUND))
			{
				player->OnGround(dt);
			}
		}
	}

	for (std::vector<Portal*>::iterator it = portals.begin(); it != portals.end(); ++it)
	{
		if ((*it) == nullptr) continue;

		if (player->CheckCollision((*it)))
		{
			player->Collision(*it);

			// �÷��̾ ��Ż�� ������ ��
			if ((*it)->GetInteractionType() == Interaction_Type::PORTAL)
			{
				std::cout << player->GetName() << " Collision Portal" << std::endl;
				(*it)->Interaction();
				return;
			}
		}
	}
}

void Map::LoadMap(std::string dataFilepath)
{
	rapidcsv::Document dataFile(dataFilepath);

	vector<string> colName = dataFile.GetColumn<string>("NAME");
	vector<int> colIndex = dataFile.GetColumn<int>("INDEX");
	vector<int> colLayer = dataFile.GetColumn<int>("LAYER");
	vector<float> colX = dataFile.GetColumn<float>("X");
	vector<float> colY = dataFile.GetColumn<float>("Y");
	vector<float> colRotate = dataFile.GetColumn<float>("ROTATE");

	int totalObjects = colName.size();
	for (int i = 0; i < totalObjects; ++i)
	{
		MapData data;
		data.name = colName[i];
		data.index = colIndex[i];
		data.layer = colLayer[i];
		data.x = colX[i];
		data.y = colY[i];
		data.rotate = colRotate[i];

		if (data.name != "portal")
		{
			AddObject(data);
			if (object != nullptr)
				stableObjects.push_back(object);
		}
		else if (data.name == "portal")
		{
			// ��Ż�� ��Ż����
			Portal* portal = new Portal();
			portal->SetCurrMap(MAP_TYPE::Town);
			// temp
			portal->SetNextMap(MAP_TYPE::KingsPass);
			portal->SetPosition(data.x, data.y);
			portals.push_back(portal);
		}
	}

	cout << "Load Complete" << endl;
}

void Map::AddObject(MapData& data)
{
	if (data.name == "ground")
	{
		this->object = new Ground(data.index);
	}
	else if (data.name == "layered")
	{
		this->object = new TownLayered(data.index);
	}
	else if (data.name == "portal")
	{
		this->object = new Portal();
	}
	else if (data.name == "building")
	{
		this->object = new TownBuilding(data.index);
	}
	else if (data.name == "bg")
	{
		this->object = new TownBG(data.index);
	}
	else if (data.name == "graveCross")
	{
		this->object = new TownGraveCross(data.index);
	}
	else if (data.name == "extra")
	{
		this->object = new TownExtra(data.index);
	}
	else if (data.name == "bench")
	{
		this->object = new Bench();
	}
	else if (data.name == "platform")
	{
		this->object = new Platform(data.index);
	}
	else if (data.name == "thorn")
	{
		this->object = new thorn();
	}
	else if (data.name == "wall")
	{
		this->object = new Wall(data.index);
	}
	else if (data.name == "kpGround")
	{
		this->object = new KingsPassGround(data.index);
	}
	else if (data.name == "kpDoor")
	{
		this->object = new Door(data.index);
	}
	else if (data.name == "kpImages")
	{
		this->object = new KingsPassImages(data.index);
	}
	else if (data.name == "kpBG")
	{
		this->object = new KingsPassBG(data.index);
	}
	else if (data.name == "kpWall")
	{
		this->object = new KingsPassWall(data.index);
	}
	else if (data.name == "kpObjects")
	{
		this->object = new KingsPassObjects(data.index);
	}

	this->object->SetLayer(data.layer);
	this->object->SetPosition(Vector2f(data.x, data.y));
	this->object->SetOriginCenter();
	this->object->GetSprite().setRotation(data.rotate);
}

