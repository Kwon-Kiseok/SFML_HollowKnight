#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include <string>
#include <unordered_map>


class Map;
class Player;
enum class MAP_TYPE
{
	Town,
	KingsPass,
	CrossRoad,
};

class MapManager : public Singleton<MapManager>
{
private:
	Map* map;
	Player* player;
public:
	MapManager() noexcept = default;
	~MapManager() noexcept;

public:

	void Init();
	void LoadMap(MAP_TYPE type);
	void Update(float dt);
	void Render(sf::RenderWindow& window);
	void Release();

	Map* GetCurrentMap();
};

