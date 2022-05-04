#include "DemoTile.hpp"

DemoTile::DemoTile()
{
}

DemoTile::DemoTile(float x, float y)
	: position(x, y)
{
	shape.setSize(Vector2f(3600, 20));
	shape.setPosition(position);
	shape.setFillColor(Color::White);
	shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
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
