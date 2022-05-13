#include "Map.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
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

#include "../Objects/Stable/CrossRoadImages.hpp"
#include "../Objects/Stable/BossRoomImages.hpp"
#include "../Objects/Stable/Central.hpp"

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
		if ((*it)->CompareTag(TAG::MONSTER))
		{
			if (InputManager::GetInstance().GetKeyDown(Keyboard::P))
			{
				std::cout << (*it)->GetName() << " X: " << (*it)->GetPosition().x << " Y: " << (*it)->GetPosition().y << std::endl;
			}

			(*it)->Update(dt, player->GetPosition());
			continue;
		}
		(*it)->Update(dt);
	}

	PlayerDataManager::GetInstance().UpdatePlayerData(*player);
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

	for (auto it = colliders.begin(); it != colliders.end(); ++it)
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

	for (auto it = colliders.begin(); it != colliders.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}
	colliders.clear();
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
				//std::cout << player->GetName() << " Collision Monster" << std::endl;
			}
			if ((*it)->CompareTag(TAG::COIN))
			{
				player->AddCoin(1);
				// 삭제
				it = gameObjects.erase(it);
				break;
			}
		}		
	}

	for (std::vector<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			if ((*it)->CompareTag(TAG::COLLIDER))
			{
				player->OnGround((*it)->GetShape().getGlobalBounds());
			}
		}
	}

	for (std::vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			player->Collision(*it);
			//player->GetHitBox().getGlobalBounds().intersects((*it)->GetSprite().getGlobalBounds());

			// 플레이어와 몬스터가 충돌했을 경우
			if ((*it)->CompareTag(TAG::MONSTER) && (*it)->GetIsAlivve())
			{
				player->SetHP(dt);
			}
		}
		/******************************************
		* 몬스터가 플레이어의 공격박스에 부딪혔을 경우
		******************************************/
		RectangleShape attackBox = player->GetAttackBox();
		if (((*it)->Collision_AttackBox(attackBox) && (*it)->CompareTag(TAG::MONSTER)) &&
			player->GetIsAttackBox() && (*it)->GetIsAlivve())
		{
			player->UpdateCollision();
			player->SetIsAttackBox(false);
			(*it)->SetHealth(-1);

			Coin* coin = new Coin((*it)->GetPosition());
			//std::cout << coin->GetName() << std::endl;
			gameObjects.push_back(coin);
		}

		if ((*it)->CompareTag(TAG::MONSTER))
		{
			// 몬스터랑 바닥 충돌처리
			for (std::vector<Collider*>::iterator collider_it = colliders.begin(); collider_it != colliders.end(); ++collider_it)
			{
				if ((*it)->CheckCollision(*collider_it))
				{
					if ((*collider_it)->CompareTag(TAG::COLLIDER))
					{
						// 몬스터랑 바닥 충돌처리
						(*it)->OnGround((*collider_it)->GetShape().getGlobalBounds());
					}
				}
			}
			// 플레이어 추격
			if ((*it)->GetDetectShape().getGlobalBounds().intersects(player->GetGlobalBounds()))
			{
				(*it)->SetIsDetect(true);
			}
		}
	}

	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			// 벤치와 부딪혔을 때
			if ((*it)->CompareTag(TAG::BENCH))
			{
				if (InputManager::GetInstance().GetKeyDown(Keyboard::Up))
				{
					(*it)->SetInteractable(true);
					(*it)->Interaction(*player);
				}
			}
		}
	}

	for (std::vector<Portal*>::iterator it = portals.begin(); it != portals.end(); ++it)
	{
		if ((*it) == nullptr) continue;

		if (player->CheckCollision((*it)))
		{
			player->Collision(*it);

			// 플레이어가 포탈과 겹쳤을 때
			if ((*it)->GetInteractionType() == Interaction_Type::PORTAL)
			{
				// 위키를 눌러서 다음 맵 이동
				if (InputManager::GetInstance().GetKeyDown(Keyboard::Up))
					(*it)->SetInteractable(true);
				if((*it)->IsInteractable())
					(*it)->Interaction(*player);
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
	vector<float> colSize_x = dataFile.GetColumn<float>("SIZE_X");
	vector<float> colSize_y = dataFile.GetColumn<float>("SIZE_Y");

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
		data.size_x = colSize_x[i];
		data.size_y = colSize_y[i];

		if (data.name != "collider")
		{
			AddObject(data);
			if (object != nullptr)
				stableObjects.push_back(object);
		}
		else if (data.name == "collider")
		{
			LoadCollision(data);
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
	else if (data.name == "elev")
	{
		this->object = new CrossRoadElev(data.index);
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
	else if (data.name == "crGround")
	{
		this->object = new CrossRoadGround(data.index);
	}
	else if (data.name == "crImages")
	{
		this->object = new CrossRoadImages(data.index);
	}
	else if (data.name == "crBG")
	{
		this->object = new CrossRoadBG(data.index);
	}
	else if (data.name == "crRoof")
	{
		this->object = new CrossRoadRoof(data.index);
	}
	else if (data.name == "crWall")
	{
		this->object = new CrossRoadWall(data.index);
	}
	else if (data.name == "crObjects")
	{
		this->object = new CrossRoadObjects(data.index);
	}
	else if (data.name == "bossRoom")
	{
		this->object = new BossRoomImages(data.index);
	}
	else if (data.name == "central")
	{
		this->object = new Central(data.index);
	}

	this->object->SetLayer(data.layer);
	this->object->SetPosition(Vector2f(data.x, data.y));
	this->object->SetOriginCenter();
	this->object->GetSprite().setRotation(data.rotate);
}

void Map::LoadCollision(MapData& data)
{
	this->collider = new Collider(Vector2f(data.size_x, data.size_y), Vector2f(data.x, data.y));
	if(nullptr != collider)
		colliders.push_back(collider);
}

