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
	for (auto it = characters.begin(); it != characters.end(); ++it)
	{
		if ((*it)->CompareTag(TAG::PLAYER))
		{
			return;
		}
	}
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

	for (auto it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if ((*it)->CompareTag(TAG::ELEVATOR))
		{
			(*it)->Update(dt);
		}	
	}

	PlayerDataManager::GetInstance().UpdatePlayerData(*player);
	ViewManager::GetInstance().TracePlayer(*player, maps_min_size, maps_max_size);

}

void Map::Render(sf::RenderWindow& window)
{


	for (int i = MAX_LAYER; i >= MIN_LAYER; --i)
	{
		for (auto it = stableObjects.begin(); it != stableObjects.end(); ++it)
		{
			if ((*it)->GetLayer() == i)
			{
				(*it)->Render(window);
			}

			if (MapManager::GetInstance().GetIsDebugMode())
			{
				window.draw((*it)->GetRectangleShape());
			}
		}
		for (auto it = characters.begin(); it != characters.end(); ++it)
		{
			if ((*it)->GetLayer() == i)
			{
				(*it)->Render(window);
			}
		}
	}

	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Render(window);
	}

	for (auto it = portals.begin(); it != portals.end(); ++it)
	{
		(*it)->Render(window);
	}

	if (MapManager::GetInstance().GetIsDebugMode())
	{
		for (auto it = colliders.begin(); it != colliders.end(); ++it)
		{
			(*it)->Render(window);
		}
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
			if ((*it)->CompareTag(TAG::COIN))
			{
				player->AddCoin(1);
				SoundManager::GetInstance().PlaySound(L"coin");
				it = gameObjects.erase(it);
				break;
			}
		}
		if ((*it)->CompareTag(TAG::COIN))
		{
			for (std::vector<Collider*>::iterator col_it = colliders.begin(); col_it != colliders.end(); ++col_it)
			{
				if (*col_it == nullptr) continue;

				// ???????????? ????????? ????????? ??????
				(*it)->Collision(*col_it);
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
    /**********************************************************
		* ?????? ????????? ??????
		**********************************************************/
		if (player->GetAttackBox().getGlobalBounds().intersects((*it)->GetShape().getGlobalBounds()))
		{
			if (player->GetPosition().x > (*it)->GetShape().getGlobalBounds().left + (*it)->GetShape().getGlobalBounds().width ||
				player->GetPosition().x < (*it)->GetShape().getGlobalBounds().left)
			{
				player->UpdateCollision(1);
				player->SetIsAttackBox(false);
			}
		}
	}
	
	for (std::vector<Character*>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if (*it == nullptr) continue;
		/**********************************************************
		* ??????????????? ????????? ??????????????? ???????????? ??????
		**********************************************************/
		if (player->GetGlobalBounds().intersects((*it)->GetAttackShape().getGlobalBounds()))
		{
			if ((*it)->GetIsAlivve() && (*it)->GetIsIsShield())
			{
				SoundManager::GetInstance().PlaySound(L"damage");
				player->OnHitted((*it)->GetPosition());
				player->SetHP();
			}
		}
		/**********************************************************
		* ??????????????? ???????????? ???????????? ??????
		**********************************************************/
		else if ((*it)->CompareTag(TAG::MONSTER) && (*it)->GetRectangleShape().getGlobalBounds().intersects(player->GetHitBox().getGlobalBounds()))
		{
			if ((*it)->GetIsAlivve() && (*it)->GetIsIsShield())
			{
				SoundManager::GetInstance().PlaySound(L"damage");
				player->OnHitted((*it)->GetPosition());
				player->SetHP();
			}
		}
		/**********************************************************
		* ???????????? ??????????????? ??????????????? ???????????? ??????
		**********************************************************/
		RectangleShape attackBox = player->GetAttackBox();
		if (((*it)->Collision_AttackBox(attackBox) && (*it)->CompareTag(TAG::MONSTER)) &&
			player->GetIsAttackBox() && (*it)->GetIsAlivve())
		{
			player->UpdateCollision(0);
			player->SetIsAttackBox(false);
			(*it)->SetHealth(-1);
			(*it)->SetShield(-1);
			Coin* coin = new Coin((*it)->GetPosition());	// ??? ?????? ?????? ?????????
			gameObjects.push_back(coin);
		}
		/**********************************************************
		* ???????????? ?????? ????????????
		**********************************************************/
		if ((*it)->CompareTag(TAG::MONSTER))
		{
			for (std::vector<Collider*>::iterator collider_it = colliders.begin(); collider_it != colliders.end(); ++collider_it)
			{
				if ((*it)->CheckCollision(*collider_it))
				{
					if ((*collider_it)->CompareTag(TAG::COLLIDER))
					{
						(*it)->OnGround((*collider_it)->GetShape().getGlobalBounds());
					}
				}
			}
			// ???????????? ??????
			if ((*it)->GetDetectShape().getGlobalBounds().intersects(player->GetGlobalBounds()))
			{
				(*it)->SetIsDetect(true);
			}
		}
	}

	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		/**********************************************************
		* ????????? ??????	????????? ???????????? ????????? ????????? ????????? ??? ?????????
		**********************************************************/
		if ((*it)->GetSprite().getGlobalBounds().intersects(player->GetAttackBox().getGlobalBounds()) &&
			((*it)->CompareTag(TAG::TRAP) && player->GetIsAttackBox()))
		{
			SoundManager::GetInstance().PlaySound(L"parry");
			player->UpdateCollision(2);
			player->SetIsAttackBox(false);
		}
		if (player->CheckCollision(*it))
		{
			if(InputManager::GetInstance().GetKeyDown(Keyboard::Up))
				player->Interaction_Stable(*it);
			/**********************************************************
			* ??????
			**********************************************************/
			if ((*it)->CompareTag(TAG::TRAP))
			{
				(*it)->Interaction(*player);
				player->OnHitted((*it)->GetPosition());
				player->SetHP();
			}
		}		
	}

	for (std::vector<Portal*>::iterator it = portals.begin(); it != portals.end(); ++it)
	{
		if ((*it) == nullptr) continue;
	
		if (player->CheckCollision((*it)))
		{
			// ??????????????? ????????? ????????? ???
			if ((*it)->GetInteractionType() == Interaction_Type::PORTAL)
			{
				// ????????? ????????? ?????? ??? ??????
				if (InputManager::GetInstance().GetKeyDown(Keyboard::Up))
				{
					(*it)->SetInteractable(true);
					return;
				}
				player->Interaction_Portal((*it));
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
	if (nullptr != collider)
		colliders.push_back(collider);
}

Vector2f& Map::GetMapsMinSize()
{
	return maps_min_size;
}

Vector2f& Map::GetMapsMaxSize()
{
	return maps_max_size;
}

