#include "PlayerDataManager.hpp"

void PlayerDataManager::SavePlayerData(Player& player)
{
	hp = player.GetHP();
	mp = player.GetMP();
}

int PlayerDataManager::GetPlayerHP()
{
	return hp;
}

int PlayerDataManager::GetPlayerMP()
{
	return mp;
}