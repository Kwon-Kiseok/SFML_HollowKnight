#include "thorn.hpp"

thorn::thorn()
	:Stable()
{
	SetTag(TAG::TRAP);
	collidable = true;
	interactable = true;
	type = Interaction_Type::DAMAGED;
	SetName("thorn");

	SetTexture("Resources/Sprite/thorn.png");
	SetSprite();
	SetOriginCenter();
}

thorn::~thorn()
{
}
