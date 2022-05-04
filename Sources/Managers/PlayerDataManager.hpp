#pragma once
#include "../include/Singleton.hpp"
#include "../Player/Player.hpp"
#include "../Managers/MapManager.hpp"

class PlayerDataManager : public Singleton<PlayerDataManager>
{
private:
	int hp;
	int mp;
	MAP_TYPE currentMap;

public:
	PlayerDataManager() {}
	~PlayerDataManager() {}

	void SavePlayerData(Player& player);
	int GetPlayerHP();
	int GetPlayerMP();
};

