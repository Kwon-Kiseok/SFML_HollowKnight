#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.hpp"
#include "../Objects/Stable/Stable.hpp"
#include "../Objects/Stable/Portal.hpp"
#include "../Objects/Collider.hpp"
#include <vector>

#include <iostream>

#define MAX_LAYER 10
#define MIN_LAYER -1

struct MapData
{
	std::string name;
	int index;
	int layer;
	float x;
	float y;
	float rotate;
	float size_x;
	float size_y;
};

class Stable;
class Map
{
protected:
	std::vector<GameObject*> gameObjects;
	std::vector<Character*> characters;
	std::vector<Collider*> colliders;
	std::vector<Stable*> stableObjects;
	std::vector<Portal*> portals;

	Player* player;
	Stable* object;
	Collider* collider;
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
	virtual void LoadCollision(MapData& data);
};

