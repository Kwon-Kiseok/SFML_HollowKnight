#include "Map.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/MapManager.hpp"

void Map::Init()
{
}

void Map::Update(float dt)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Update(dt);
	}

	ViewManager::GetInstance().GetMainView().setCenter(player->GetPosition());
}

void Map::Render(sf::RenderWindow& window)
{
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		(*it)->Render(window);
	}

	for (auto it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		(*it)->Render(window);
	}
}

void Map::Release()
{
}

void Map::CheckCollisions()
{
	for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			player->Collision(*it);
		}
	}

	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (player->CheckCollision(*it))
		{
			player->Collision(*it);

			// ÇÃ·¹ÀÌ¾î°¡ Æ÷Å»°ú °ãÃÆÀ» ¶§
			if ((*it)->GetInteractionType() == Interaction_Type::PORTAL)
			{
				std::cout << player->GetName() << " Collision Portal" << std::endl;
				(*it)->Interaction();
				return;
			}

			// ¶¥°ú ºÎµúÇûÀ» ¶§
			if ((*it)->CompareTag(TAG::GROUND))
			{
				std::cout << player->GetName() << " Collision Stable" << std::endl;
			}
		}

	}
}

