#include "Wall.hpp"

Wall::Wall()
{
	index_total = 17;
}

Wall::Wall(int idx)
	: Stable()
{
	index_total = 17;
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
	std::string path = "Resources/Sprite/wall_";
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
	case 4:
		index = "04.png";
		break;
	case 5:
		index = "05.png";
		break;
	case 6:
		index = "06.png";
		break;
	case 7:
		index = "07.png";
		break;
	case 8:
		index = "08.png";
		break;
	case 9:
		index = "01_r.png";
		break;
	case 10:
		index = "02_r.png";
		break;
	case 11:
		index = "03_r.png";
		break;
	case 12:
		index = "04_r.png";
		break;
	case 13:
		index = "05_r.png";
		break;
	case 14:
		index = "06_r.png";
		break;
	case 15:
		index = "07_r.png";
		break;
	case 16:
		index = "black_l.png";
		break;
	case 17:
		index = "black_r.png";
		break;

	}

	SetName("wall");
	SetTexture(path + index);
	SetSprite();

}

Wall::~Wall()
{
}
