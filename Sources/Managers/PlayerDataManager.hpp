#pragma once
#include "../include/Singleton.hpp"
#include "../Player/Player.hpp"
#include "../Managers/MapManager.hpp"
#include "../Items/Coin.hpp"

class PlayerDataManager : public Singleton<PlayerDataManager>
{
private:
	int hp = 5;
	int mp;
	int coin;
	MAP_TYPE currentMap;

public:
	PlayerDataManager() {}
	~PlayerDataManager() {}

	void UpdatePlayerData(Player& player);
	int GetPlayerHP();
	int GetPlayerMP();
	int GetPlayerCoin();
	MAP_TYPE GetPlayerCurrentMap();
	int AddCoin(int value);
};

