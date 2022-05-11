#include "Coin.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/TextureManager.hpp"

Coin::Coin(Vector2f pos)
{
	position = pos;
}

void Coin::Init()
{
	texture = TextureManager::GetInstance().GetTexture("Resourcese/Sprite/UI/HUD_coin_shop.png");
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Coin::Update(float dt)
{
	Vector2f delta;
	gravity += Gravity * dt;
	isFalling = true;
	if (gravity > 1000.f)
	{
		gravity = 1000.f;
	}
	delta.y = gravity * dt;
}

void Coin::Render(RenderWindow& window)
{
	window.draw(sprite);
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
		int y = Utility::Random(_velocity_y, _velocity_y + gravity);

		sprite.setPosition(Vector2f(position.x + x, position.y + y));
		pickCoin = true;
	}
}
