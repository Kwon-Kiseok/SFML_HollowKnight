#include "Coin.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Objects/Moveable/Monster/Monster.hpp"

Coin::Coin(Vector2f pos)
{
	position = pos;
	Init();
}

void Coin::Init()
{
	SetTag(TAG::COIN);
	SetName("coin");
	isFalling = true;

	texture = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/HUD_coin_v020004_.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().height+20.f);
	sprite.setPosition(position);

	//int x = Utility::Random(0, _velocity_x);
	//int y = Utility::Random(_velocity_y, _velocity_y + fallingSpeed);

	//sprite.setPosition(Vector2f(position.x + x, position.y + y));
}

void Coin::Update(float dt)
{
	if (isFalling)
	{
		fallingSpeed += GRAVITY * dt;
		if (fallingSpeed > 500.f)
		{
			fallingSpeed = 500.f;
		}
		position.y += fallingSpeed * dt;
		sprite.setPosition(position);
	}
}


void Coin::Render(RenderWindow& window)
{
	window.draw(sprite);
}

void Coin::OnGround()
{
	isFalling = false;
	Vector2f pos = sprite.getPosition();
	isCollideCoin = true;

	sprite.setPosition(pos);
	PositionCoin = pos;
	sprite.setPosition(pos);
}

int Coin::PickUp()
{
	SoundManager::GetInstance().PlaySound(L"coin");
	pickCoin = false;
	return value;
}

void Coin::SetPosition(Vector2f crawlidPosition)
{
	sprite.setPosition(crawlidPosition);
}

FloatRect Coin::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

bool Coin::Collision(GameObject* otherObj)
{
	if (this->GetSprite().getGlobalBounds().intersects(otherObj->GetRectangleShape().getGlobalBounds()))
	{
		OnGround();
		return true;
	}
	return false;
}
