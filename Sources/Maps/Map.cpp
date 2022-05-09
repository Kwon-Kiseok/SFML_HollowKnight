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
			player->Collision(*it);

			// �÷��̾ ��Ż�� ������ ��
			if ((*it)->GetInteractionType() == Interaction_Type::PORTAL)
			{
				std::cout << player->GetName() << " Collision Portal" << std::endl;
				(*it)->Interaction();
				return;
			}

			// ���� �ε����� ��
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

