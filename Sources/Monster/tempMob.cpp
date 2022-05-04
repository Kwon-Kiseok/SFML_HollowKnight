#include "tempMob.hpp"

void tempMob::Init()
{
	SetTexture("Resources/Sprite/Spawn_02.png");
	SetTag(TAG::MONSTER);
	SetSprite();
	SetOriginCenter(); // �ӽ� idle �ִϸ��̼� ���� ����
	SetLayer(0); // �ӽ�
	
	DebugCollision(Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
}

void tempMob::Update(float dt)
{
	static float timer;
	timer += dt;
	sprite.setPosition(GetPosition());
	rectangleShape.setPosition(sprite.getPosition());

	if (timer/3.f >= 1)
	{
		SetPosition(Vector2f(GetPosition().x - 20.f, GetPosition().y));
		timer = 0;
	}
}

void tempMob::Render(RenderWindow& window)
{
	window.draw(rectangleShape);
	window.draw(sprite);
}

void tempMob::Release()
{
}
