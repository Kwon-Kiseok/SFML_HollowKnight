#include "Platform.hpp"
#include "../Collider.hpp"

#include <iostream>

Platform::Platform()
{
	index_total = 11;
}

Platform::Platform(int idx)
	:Stable()
{
	index_total = 11;
	SetTag(TAG::GROUND);
	collidable = true;
	interactable = false;
	type = Interaction_Type::NONE;
	imageIdx = idx;
	std::string path = "Resources/Sprite/";
	std::string index;

	switch (imageIdx)
	{
	case 1:
		index = "plat_float_01.png";
		break;
	case 2:
		index = "plat_float_02.png";
		break;
	case 3:
		index = "plat_float_03.png";
		break;
	case 4:
		index = "plat_float_04.png";
		break;
	case 5:
		index = "plat_float_05.png";
		break;
	case 6:
		index = "plat_float_06.png";
		break;
	case 7:
		index = "plat_float_07.png";
		break;
	case 8:
		index = "plat_float_08.png";
		break;
	case 9:
		index = "plat_float_09.png";
		break;
	case 10:
		index = "plat_float_10.png";
		break;
	case 11:
		path += "BG/CrossRoad/CentralResource/";
		index = "central_elev.png";
		break;
	}

	SetName("platform");
	SetTexture(path + index);
	SetSprite();
}

Platform::~Platform()
{
}

void Platform::Update(float dt)
{
	switch (platformType)
	{
	case PLATFORM_TYPE::FIXED:
		break;
	case PLATFORM_TYPE::ELEVEATOR:
		Elevate(dt);
		break;
	case PLATFORM_TYPE::SIDEMOVE:
		break;
	case PLATFORM_TYPE::FALLEN:
		break;
	}
}

void Platform::SetElevator(float endPos, int dir, float speed)
{
	SetTag(TAG::ELEVATOR);
	startPos = position;
	this->endPos.x = position.x;
	this->endPos.y = endPos;
	this->direction = dir;
	this->speed = speed;
	type = Interaction_Type::ELEVATOR;
	platformType = PLATFORM_TYPE::ELEVEATOR;
	collider = new Collider(Vector2f(235.f, 60.f), startPos);
	collider->SetOriginCenter();
}

void Platform::Elevate(float dt)
{
	if (!elevatorTrigger)
	{
		return;
	}
	float displacement = direction * speed * dt;
	position.y += displacement;
	SetPosition(position);
	collider->SetPosition(position);

	if (direction == 1 && (position.y >= endPos.y + displacement || position.y >= endPos.y - displacement))
	{
		direction *= -1;
		elevatorTrigger = false;
		SetInteractable(false);
		Vector2f swapPos;
		swapPos = startPos;
		startPos = endPos;
		endPos = swapPos;
	}
	else if(direction == -1 && (position.y <= endPos.y + displacement || position.y <= endPos.y - displacement))
	{
		direction *= -1;
		elevatorTrigger = false;
		std::cout << "Arrive endPos" << std::endl;
		SetInteractable(false);
		Vector2f swapPos;
		swapPos = startPos;
		startPos = endPos;
		endPos = swapPos;
	}
}

Collider* Platform::GetCollider()
{
	return collider;
}

void Platform::Interaction(Player& player)
{
	switch (platformType)
	{
	case PLATFORM_TYPE::FIXED:
		break;
	case PLATFORM_TYPE::ELEVEATOR:
		elevatorTrigger = true;
		break;
	case PLATFORM_TYPE::SIDEMOVE:
		break;
	case PLATFORM_TYPE::FALLEN:
		break;
	}
}
