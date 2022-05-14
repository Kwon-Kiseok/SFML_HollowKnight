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

void Collider::SetPosition(Vector2f pos)
{
	position = pos;
	rectangleShape.setPosition(position);
}

void Collider::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	rectangleShape.setPosition(position);
}

void Collider::SetOriginCenter()
{
	rectangleShape.setOrigin(rectangleShape.getGlobalBounds().width / 2, rectangleShape.getGlobalBounds().height / 2);
}
