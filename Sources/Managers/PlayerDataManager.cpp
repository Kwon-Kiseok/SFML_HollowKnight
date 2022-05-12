#include "PlayerDataManager.hpp"

void PlayerDataManager::UpdatePlayerData(Player& player)
{
	hp = player.GetHP();
	mp = player.GetMP();
	coin = player.GetCoin();
	currentMap = player.GetCurrentMap();
}

int PlayerDataManager::GetPlayerHP()
{
	return hp;
}

int PlayerDataManager::GetPlayerMP()
{
	return mp;
}

int PlayerDataManager::GetPlayerCoin()
{
	return coin;
}

MAP_TYPE PlayerDataManager::GetPlayerCurrentMap()
{
	return currentMap;
}

int PlayerDataManager::AddCoin(int value)
{
	return this->coin += value;
}
