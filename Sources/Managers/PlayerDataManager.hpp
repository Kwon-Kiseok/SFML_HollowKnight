#pragma once
#include "../include/Singleton.hpp"
#include "../Player/Player.hpp"

class PlayerDataManager : public Singleton<PlayerDataManager>
{
private:
	int hp;
	int mp;

public:
	PlayerDataManager() {}
	~PlayerDataManager() {}

	void SavePlayerData(Player& player);
	int GetPlayerHP();
	int GetPlayerMP();
};

