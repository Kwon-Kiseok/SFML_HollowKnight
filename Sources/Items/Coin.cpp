#include "Coin.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Objects/Moveable/Monster/Monster.hpp"

Coin::Coin(Vector2f pos)
{
	position = pos;
}

void Coin::Init()
{
	SetTag(TAG::COIN);
	texture = TextureManager::GetInstance().GetTexture("Resourcese/Sprite/UI/HUD_coin_shop.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().height);
	sprite.setPosition(position);
}

void Coin::Update(float dt)
{
	//if (isFalling)
	//{
	//	fallingSpeed += GRAVITY * dt;
	//	if (fallingSpeed > 3000.f)
	//	{
	//		fallingSpeed = 3000.f;
	//	}
	//	PositionCoin.y = fallingSpeed * dt;
	//}
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

void Coin::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned)
	{
		int x = Utility::Random(0, _velocity_x);
		int y = Utility::Random(_velocity_y, _velocity_y + fallingSpeed);

		sprite.setPosition(Vector2f(position.x + x, position.y + y));
		pickCoin = true;
	}

}

void Coin::SetPosition(Vector2f crawlidPosition)
{
	sprite.setPosition(crawlidPosition);
}

FloatRect Coin::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}
