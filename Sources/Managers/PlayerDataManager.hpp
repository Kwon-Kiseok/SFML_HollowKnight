#pragma once
#include "../include/Singleton.hpp"
#include "../Player/Player.hpp"
#include "../Managers/MapManager.hpp"
#include "../Items/Coin.hpp"

#define MAX_HEALTH 5


class PlayerDataManager : public Singleton<PlayerDataManager>
{
private:
	int hp = MAX_HEALTH;
	int mp;
	int coin;
	MAP_TYPE savePointMap;
	Vector2f lastBenchPos;
	MAP_TYPE currentMap;
	Vector2f lastPosition;
	int profileNumber = 0;

public:
	PlayerDataManager() {}
	~PlayerDataManager() {}

	void UpdatePlayerData(Player& player);
	void SavePlayerData(Player& player);
	void LoadPlayerData(Player& player);
	int GetPlayerHP();
	int GetPlayerMP();
	int GetPlayerCoin();
	MAP_TYPE GetPlayerCurrentMap();
	MAP_TYPE GetSavePointMap();
	void SaveBenchPoint(Vector2f pos);
	Vector2f GetBenchPoint();
	int AddCoin(int value);
};

