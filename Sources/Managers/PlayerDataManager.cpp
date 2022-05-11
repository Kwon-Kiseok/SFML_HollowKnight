#include "PlayerDataManager.hpp"

void PlayerDataManager::SavePlayerData(Player& player)
{
	hp = player.GetHP();
	mp = player.GetMP();
	coin = player.GetCoin();
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
