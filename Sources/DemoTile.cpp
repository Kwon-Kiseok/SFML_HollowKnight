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
	return shape.getGlobalBounds();	// 충돌 체크
}

const RectangleShape& DemoTile::GetShape()
{
	return shape; // 렌더링 할 때 사용
}

void DemoTile::Update(float dt)
{

}
