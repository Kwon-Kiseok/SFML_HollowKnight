#pragma once
#include <SFML/Graphics.hpp>
#include "../include/Singleton.hpp"
#include <string>
#include <map>


class Map;
class Player;
enum class MAP_TYPE
{
	Town,
	KingsPass,
	CrossRoad,
	BossRoom,
	Count,
};

class MapManager : public Singleton<MapManager>
{
private:
	Map* map;
	std::map<MAP_TYPE, Map*> maps;
	Player* player;
	std::map<MAP_TYPE, sf::Vector2f> startPos;

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
	void SetStartPos(MAP_TYPE type, sf::Vector2f pos);
};

