#include "Stable.hpp"

Stable::Stable()
	: GameObject()
{
	collidable = false;
	interactable = false;
	type = Interaction_Type::NONE;
}

Stable::~Stable()
{
}

bool Stable::IsCollidable()
{
	return collidable;
}

bool Stable::IsInteractable()
{
	return interactable;
}

Interaction_Type Stable::GetInteractionType()
{
	return type;
}

void Stable::Interaction()
{
	return;
}

int Stable::GetIndexTotal()
{
	return index_total;
}

void Stable::Init()
{
}

void Stable::Render(RenderWindow& window)
{
	window.draw(this->sprite);
}

void Stable::Update(float dt)
{

	return;
}

bool Stable::Collision(GameObject* otherObj)
{
	return false;
}

void Stable::Release()
{
}
