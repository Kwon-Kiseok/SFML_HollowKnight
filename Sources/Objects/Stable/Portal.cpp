#include "Portal.hpp"

Portal::Portal()
	: Stable()
{
	SetTag(TAG::NONE);
	collidable = true;
	interactable = true;
	type = Interaction_Type::PORTAL;
	nextMap = MAP_TYPE::KingsPass;

	SetTexture("Resources/Sprite/light_effect_v02.png");
	SetSprite();
	SetOriginCenter();

	DebugCollision(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	rectangleShape.setPosition(sprite.getPosition());
}

Portal::~Portal()
{
}

void Portal::Interaction()
{
	MapManager::GetInstance().LoadMap(nextMap);
}

void Portal::Render(RenderWindow& window)
{
	window.draw(rectangleShape);
	window.draw(sprite);
}

bool Portal::Collision(GameObject* otherObj)
{
	return false;
}
