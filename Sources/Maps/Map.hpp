#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.hpp"
#include "../Objects/Stable/Stable.hpp"
#include <vector>

#include <iostream>

class Map
{
protected:
	std::vector<GameObject*> gameObjects;
	std::vector<Character*> characters;

	std::vector<Stable*> stableObjects;

	Player* player;
public:
	Map(Player* player_) : player(player_) {}
	virtual ~Map() {}

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow& window);
	virtual void Release();

	virtual void CheckCollisions(float dt);
};

