#include "Ground.hpp"
#include "../../Utils/Utility.hpp"
#include <string>

Ground::Ground()
	: Stable()
{
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;

	std::string path = "Resources/Sprite/BG/Town/town_floor_";
	std::string index;
	int randNum = Utility::Random(1, 4);

	switch (randNum)
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

