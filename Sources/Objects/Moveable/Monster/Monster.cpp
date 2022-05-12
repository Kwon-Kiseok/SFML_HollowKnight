#include "Monster.hpp"
#include "../../../Managers/InputManager.hpp"

Monster::Monster()
{
	startPos = Vector2f(0.f, 0.f);
	endPos = Vector2f(0.f, 0.f);
}

Monster::~Monster()
{
}

Vector2f Monster::GetStartPos()
{
	return startPos;
}

Vector2f Monster::GetEndPos()
{
	return endPos;
}
