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

}

void Coin::Render(RenderWindow& window)
{
	window.draw(sprite);
}
