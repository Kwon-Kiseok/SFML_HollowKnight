#include "Ground.hpp"
#include <string>

Ground::Ground()
	: Stable()
{
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;

	SetTexture("Resources/Sprite/BG/Town/town_floor_01.png");
	SetSprite();
}

Ground::~Ground()
{
}

bool Ground::Collision(GameObject* otherObj)
{
	return true;
}

