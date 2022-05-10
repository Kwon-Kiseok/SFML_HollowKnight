#include "PlayerDataManager.hpp"

void PlayerDataManager::SavePlayerData(Player& player)
{
	hp = player.GetHP();
	mp = player.GetMP();

	// 파일입출력으로 저장?
}

int PlayerDataManager::GetPlayerHP()
{
	return hp;
}

int PlayerDataManager::GetPlayerMP()
{
	return mp;
}