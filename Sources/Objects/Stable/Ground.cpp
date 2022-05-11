#include "Ground.hpp"
#include "../../Utils/Utility.hpp"
#include <string>

Ground::Ground()
{
	index_total = 3;
}

Ground::Ground(int idx)
	: Stable()
{
	index_total = 3;
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
	std::string path = "Resources/Sprite/BG/Town/town_floor_";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "01.png";
		break;
	case 2:
		index = "02.png";
		break;
	case 3:
		index = "03.png";
		break;
	}

	SetName("ground");
	SetTexture(path+index);
	SetSprite();
}

Ground::~Ground()
{
}

bool Ground::Collision(GameObject* otherObj)
{
	return true;
}

/// <summary>
/// 
/// </summary>
KingsPassGround::KingsPassGround()
{
	index_total = 4;
}

KingsPassGround::KingsPassGround(int idx)
	: Stable()
{
	index_total = 4;
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
	std::string path = "Resources/Sprite/BG/Tutorial/tut_land_floor_00";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "00_04.png";
		break;
	case 2:
		index = "01_03.png";
		break;
	case 3:
		index = "02_02.png";
		break;
	case 4:
		index = "03_01.png";
		break;
	}

	SetName("kpGround");
	SetTexture(path + index);
	SetSprite();
}

KingsPassGround::~KingsPassGround()
{
}

CrossRoadGround::CrossRoadGround(int idx)
	:Stable()
{
	index_total = 13;
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
	std::string path = "Resources/Sprite/BG/CrossRoad/ground/";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "break_floor_0002_c4.png";
		break;
	case 2:
		index = "break_floor_0003_c3.png";
		break;
	case 3:
		index = "break_floor_0004_c2.png";
		break;
	case 4:
		index = "break_floor_0006_b2.png";
		break;
	case 5:
		index = "break_floor_0007_b1.png";
		break;
	case 6:
		index = "break_floor_0008_a2.png";
		break;
	case 7:
		index = "break_floor_0009_a1.png";
		break;
	case 8:
		index = "break0000.png";
		break;
	case 9:
		index = "break0001.png";
		break;
	case 10:
		index = "cd_floor_02.png";
		break;
	case 11:
		index = "cd_floor_highway_05.png";
		break;
	case 12:
		index = "cd_floor_highway_06.png";
		break;
	case 13:
		index = "Hallownest_Gate_0006_14.png";
		break;
	}

	SetName("crGround");
	SetTexture(path + index);
	SetSprite();
}
