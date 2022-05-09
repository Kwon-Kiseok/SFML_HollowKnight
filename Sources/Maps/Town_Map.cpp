#include "Town_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"
#include "../Player/Player.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Objects/Stable/BackgroundImages.hpp"
#include "../Objects/Stable/Bench.hpp"
#include "../Objects/Stable/Ground.hpp"
#include "../Objects/Stable/Portal.hpp"
#include "../Objects/Stable/Stable.hpp"
#include <iostream>

Town_Map::Town_Map(Player* player)
	: Map(player)
{
	LoadMap();
	player->SetPosition(Vector2f(100.f, 700.f));
}

void Town_Map::LoadMap()
{
	rapidcsv::Document dataFile("data_tables/maps/Town_map_data.csv");

	vector<string> colName = dataFile.GetColumn<string>("NAME");
	vector<int> colIndex = dataFile.GetColumn<int>("INDEX");
	vector<int> colLayer = dataFile.GetColumn<int>("LAYER");
	vector<float> colX = dataFile.GetColumn<float>("X");
	vector<float> colY = dataFile.GetColumn<float>("Y");

	int totalObjects = colName.size();
	for (int i = 0; i < totalObjects; ++i)
	{
		MapData data;
		data.name = colName[i];
		data.index = colIndex[i];
		data.layer = colLayer[i];
		data.x = colX[i];
		data.y = colY[i];

		AddObject(data);
		stableObjects.push_back(object);
	}

	cout << "Load Complete" << endl;
}

void Town_Map::AddObject(MapData& data)
{
	if (data.name == "ground")
	{
		this->object = new Ground(data.index);
	}
	else if (data.name == "layered")
	{
		this->object = new TownLayered(data.index);
	}
	else if (data.name == "portal")
	{
		this->object = new Portal();
	}
	else if (data.name == "building")
	{
		this->object = new TownBuilding(data.index);
	}
	else if (data.name == "bg")
	{
		this->object = new TownBG(data.index);
	}
	else if (data.name == "graveCross")
	{
		this->object = new TownGraveCross(data.index);
	}
	else if (data.name == "extra")
	{
		this->object = new TownExtra(data.index);
	}
	else if (data.name == "bench")
	{
		this->object = new Bench();
	}

	this->object->SetLayer(data.layer);
	this->object->SetPosition(Vector2f(data.x, data.y));
	this->object->SetOriginCenter();
}
