#include "Collider.hpp"

Collider::Collider()
{
	SetTag(TAG::COLLIDER);
	SetName("collider");
	SetLayer(-1);
}

Collider::Collider(Vector2f size, Vector2f pos)
	:Collider()
{
	rectangleShape.setSize(size);
	position = pos;
	rectangleShape.setPosition(position);
}

Collider::~Collider()
{
}

bool Collider::Collision(GameObject* otherObj)
{
	return true;
}

void Collider::Init()
{
}

void Collider::Update(float dt)
{
}

void Collider::Render(RenderWindow& window)
{
	window.draw(rectangleShape);
}

void Collider::Release()
{
}

RectangleShape& Collider::GetShape()
{
	return rectangleShape;
}
