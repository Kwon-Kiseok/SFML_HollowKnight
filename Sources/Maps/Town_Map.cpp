#include "Town_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"

Town_Map::Town_Map()
{
}

void Town_Map::Init()
{
	textureBG.loadFromFile("Resources/Sprite/BG/Town/town_bench.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setPosition(990.f, 820.f);
	spriteBG.setOrigin(spriteBG.getLocalBounds().width / 2, spriteBG.getLocalBounds().height / 2);

}

void Town_Map::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Space))
	{
		MapManager::GetInstance().LoadMap(MAP_TYPE::KingsPass);
	}
}

void Town_Map::Render(RenderWindow& window)
{
	window.draw(spriteBG);
}

void Town_Map::Release()
{
}
