#include "Ground.hpp"
#include "../../Utils/Utility.hpp"
#include <string>

Ground::Ground(int idx)
	: Stable()
{
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

	SetTexture(path+index);
	SetSprite();
}

Ground::~Ground()
{
}

void Ground::SetImageIdx(int idx)
{
	imageIdx = idx;
}

bool Ground::Collision(GameObject* otherObj)
{
	return true;
}

