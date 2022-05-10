#include "Door.hpp"

Door::Door()
{
	index_total = 2;
}

Door::Door(int idx)
	: Stable()
{
	index_total = 2;
	SetTag(TAG::BREAKABLE);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;

	switch (imageIdx)
	{
	case 1:
		SetTexture("Resources/Sprite/BG/Tutorial/tut_door_01.png");
		break;
	case 2:
		SetTexture("Resources/Sprite/BG/Tutorial/tut_door_large_0007_04.png");
		break;
	}

	SetName("kpDoor");
	SetSprite();
}

Door::~Door()
{
}
