#include "Portal.hpp"

Portal::Portal()
	: Stable()
{
	SetTag(TAG::NONE);
	collidable = true;
	interactable = true;
	type = Interaction_Type::PORTAL;
	
	SetTexture("Resources/Sprite/light_effect_v02.png");
	SetSprite();
	SetOriginCenter();

	DebugCollision(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	rectangleShape.setPosition(sprite.getPosition());
}

Portal::~Portal()
{
}

MAP_TYPE& Portal::GetCurrentMap()
{
	return currMap;
}

void Portal::SetNextMap(MAP_TYPE next)
{
	nextMap = next;
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
