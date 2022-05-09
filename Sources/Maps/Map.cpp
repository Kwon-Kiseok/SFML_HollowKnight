#include "Map.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Managers/InputManager.hpp"
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

}

void Map::Release()
{
	for (auto it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}
	stableObjects.clear();

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

			// 플레이어와 몬스터가 충돌했을 경우
			if ((*it)->CompareTag(TAG::MONSTER))
			{
				std::cout << player->GetName() << " Collision Monster" << std::endl;
				//player->OnHitted(dt);
			}
		}
		/******************************************
		* 몬스터가 플레이어의 공격박스에 부딪혔을 경우
		* 이게 맞나요????
		******************************************/
		RectangleShape attackBox = player->GetAttackBox();
		if ((*it)->Collision_AttackBox(attackBox) && (*it)->CompareTag(TAG::MONSTER))
		{
			player->UpdateCollision();
		}

		//if (player->Collision_AttackBox((*it)->GetAttackBox()) && (*it)->CompareTag(TAG::MONSTER))
		//{
		//	// 플레이어가 몬스터의 어택박스에 적중당했을 때
		//  // 플레이어 넉백 + 데미지 판정
		//}
	}

	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			player->Collision(*it);

			// 플레이어가 포탈과 겹쳤을 때
			if ((*it)->GetInteractionType() == Interaction_Type::PORTAL)
			{
				std::cout << player->GetName() << " Collision Portal" << std::endl;
				(*it)->Interaction();
				return;
			}

			// 땅과 부딪혔을 때
			if ((*it)->CompareTag(TAG::GROUND))
			{
				player->OnGround(dt);
				std::cout << player->GetName() << " Collision Stable" << std::endl;
			}
			else
			{
				//player->SetVal(dt);
			}
		}

	}
}

