#include "Platform.hpp"

Platform::Platform()
{
	index_total = 10;
}

Platform::Platform(int idx)
	:Stable()
{
	index_total = 10;
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
	std::string path = "Resources/Sprite/";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "plat_float_01.png";
		break;
	case 2:
		index = "plat_float_02.png";
		break;
	case 3:
		index = "plat_float_03.png";
		break;
	case 4:
		index = "plat_float_04.png";
		break;
	case 5:
		index = "plat_float_05.png";
		break;
	case 6:
		index = "plat_float_06.png";
		break;
	case 7:
		index = "plat_float_07.png";
		break;
	case 8:
		index = "plat_float_08.png";
		break;
	case 9:
		index = "plat_float_09.png";
		break;
	case 10:
		index = "plat_float_10.png";
		break;
	}

	SetName("platform");
	SetTexture(path + index);
	SetSprite();
}

Platform::~Platform()
{
}
