#include "Portal.hpp"

Portal::Portal()
	: Stable()
{
	SetTag(TAG::NONE);
	collidable = true;
	interactable = true;
	type = Interaction_Type::PORTAL;
	SetName("portal");
	
	SetTexture("Resources/Sprite/light_effect_v02.png");
	SetSprite();
	SetOriginCenter();
}

Portal::~Portal()
{
}

MAP_TYPE& Portal::GetCurrentMap()
{
	return currMap;
}

MAP_TYPE& Portal::GetNextMap()
{
	return nextMap;
}

void Portal::SetCurrMap(MAP_TYPE curr)
{
	currMap = curr;
}

void Portal::SetNextMap(MAP_TYPE next, Vector2f pos)
{
	nextMap = next;
	spawnPos = pos;
}

void Portal::SetType(PORTAL_TYPE type)
{
	portalType = type;
}

void Portal::Interaction(Player& player)
{
	MapManager::GetInstance().SetStartPos(nextMap, spawnPos);
	MapManager::GetInstance().LoadMap(nextMap);
	if(portalType == PORTAL_TYPE::MANUAL)
		interactable = false;
}

void Portal::Render(RenderWindow& window)
{
	window.draw(sprite);
}

bool Portal::Collision(GameObject* otherObj)
{
	return false;
}
