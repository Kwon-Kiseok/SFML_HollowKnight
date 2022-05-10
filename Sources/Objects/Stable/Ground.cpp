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
