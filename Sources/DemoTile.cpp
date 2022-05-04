#include "DemoTile.hpp"

DemoTile::DemoTile()
{
}

DemoTile::DemoTile(float x, float y)
	: position(x, y)
{
	shape.setSize(Vector2f(500, 20));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
}

FloatRect DemoTile::GetGlobalBounds()
{
	return shape.getGlobalBounds();	// �浹 üũ
}

const RectangleShape& DemoTile::GetShape()
{
	return shape; // ������ �� �� ���
}

void DemoTile::Update(float dt)
{

}
