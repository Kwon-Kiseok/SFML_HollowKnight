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

void thorn::Interaction(Player& player)
{
	if (sprite.getLocalBounds().width / 2 < player.GetPosition().x)
	{
		moveToPos.x = position.x + 200.f;
		moveToPos.y = position.y - 200.f;
	}
	else
	{
		moveToPos.x = position.x - 200.f;
		moveToPos.y = position.y - 200.f;
	}

	player.SetPosition(moveToPos);
}
