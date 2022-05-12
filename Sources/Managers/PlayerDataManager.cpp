#include "PlayerDataManager.hpp"
#include "../Animation/rapidcsv.hpp"
#include <iostream>
#include <ostream>
#include <vector>

void PlayerDataManager::UpdatePlayerData(Player& player)
{
	hp = player.GetHP();
	mp = player.GetMP();
	coin = player.GetCoin();
	currentMap = player.GetCurrentMap();
	lastPosition = player.GetPosition();
}

void PlayerDataManager::SavePlayerData(Player& player)
{
	std::ofstream playerDataFile;
	playerDataFile.open("data_tables/player/player_save_data.csv");
	if (playerDataFile.fail())
	{
		std::cout << "playerData File load Failed" << std::endl;
		return;
	}
	playerDataFile << "HP,MP,COIN,CURR_MAP,LAST_POS_X,LAST_POS_Y\n";
	
	UpdatePlayerData(player);

	playerDataFile << hp << "," << mp << "," << coin << "," << static_cast<int>(currentMap) << "," << lastPosition.x << "," << lastPosition.y << std::endl;

}

void PlayerDataManager::LoadPlayerData(Player& player)
{
	rapidcsv::Document playerDataFile("data_tables/player/player_save_data.csv");

	std::vector<int> colHP = playerDataFile.GetColumn<int>("HP");
	std::vector<int> colMP = playerDataFile.GetColumn<int>("MP");
	std::vector<int> colCoin = playerDataFile.GetColumn<int>("COIN");
	std::vector<int> colCurrMap = playerDataFile.GetColumn<int>("CURR_MAP");
	std::vector<float> colLastPos_x = playerDataFile.GetColumn<float>("LAST_POS_X");
	std::vector<float> colLastPos_y = playerDataFile.GetColumn<float>("LAST_POS_Y");

	hp = colHP[profileNumber];
	mp = colMP[profileNumber];
	coin = colCoin[profileNumber];
	currentMap = static_cast<MAP_TYPE>(colCurrMap[profileNumber]);
	lastPosition = Vector2f(colLastPos_x[profileNumber], colLastPos_y[profileNumber]);

	player.SetHealth(hp);
	player.AddCoin(coin);
	player.SetCurrentMap(currentMap);
	player.SetPosition(lastPosition);
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
