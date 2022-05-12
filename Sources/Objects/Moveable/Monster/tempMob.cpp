#include "tempMob.hpp"

void tempMob::Init()
{
	SetTexture("Resources/Sprite/Spawn_02.png");
	SetTag(TAG::MONSTER);
	SetSprite();
	SetOriginCenter(); // 임시 idle 애니메이션 들어가면 지양
	SetLayer(0); // 임시
	SetName("tempMob");
	
	DebugCollision();
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
