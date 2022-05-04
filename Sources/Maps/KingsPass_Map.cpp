#include "KingsPass_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"

void KingsPass_Map::Init()
{
	textureBG.loadFromFile("Resources/Sprite/BG/Tutorial/tut_tab_ancient_0001_2.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setPosition(990.f, 820.f);
	spriteBG.setOrigin(spriteBG.getLocalBounds().width / 2, spriteBG.getLocalBounds().height / 2);

}

void KingsPass_Map::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Space))
	{
		MapManager::GetInstance().LoadMap(MAP_TYPE::CrossRoad);
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::BackSpace))
	{
		MapManager::GetInstance().LoadMap(MAP_TYPE::Town);
	}
}

void KingsPass_Map::Render(sf::RenderWindow& window)
{
	window.draw(spriteBG);
}

void KingsPass_Map::Release()
{
}
