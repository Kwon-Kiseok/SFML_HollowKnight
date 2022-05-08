#include "Bench.hpp"

Bench::Bench()
	:Stable()
{
	SetTag(TAG::BENCH);
	collidable = true;
	interactable = true;
	type = Interaction_Type::BENCH;
	SetName("bench");

	SetTexture("Resources/Sprite/BG/Town/town_bench.png");
	SetSprite();
	SetOriginCenter();

	/*DebugCollision(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	rectangleShape.setPosition(sprite.getPosition());*/
}

Bench::~Bench()
{
}

void Bench::Interaction()
{
	// ��ġ�� ����� ��
}

void Bench::Render(RenderWindow& window)
{
	//window.draw(rectangleShape);
	window.draw(sprite);
}

bool Bench::Collision(GameObject* otherObj)
{
	return false;
}
