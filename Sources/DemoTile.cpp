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
	return shape.getGlobalBounds();	// 충돌 체크
}

const RectangleShape& DemoTile::GetShape()
{
	return shape; // 렌더링 할 때 사용
}

void DemoTile::Update(float dt)
{

}
