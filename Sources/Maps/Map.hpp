#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.hpp"
#include "../Objects/Stable/Stable.hpp"
#include "../Objects/Stable/Portal.hpp"
#include <vector>

#include <iostream>

struct MapData
{
	std::string name;
	int index;
	int layer;
	float x;
	float y;
	float rotate;
};

class Stable;
class Map
{
protected:
	std::vector<GameObject*> gameObjects;
	std::vector<Character*> characters;
	std::vector<Stable*> stableObjects;
	std::vector<Portal*> portals;

	Player* player;
	Stable* object;

public:
	Map(Player* player_) : player(player_) {}
	virtual ~Map() {}

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow& window);
	virtual void Release();

	virtual void CheckCollisions(float dt);

	virtual void LoadMap(std::string dataFilepath);
	virtual void AddObject(MapData& data);
};

