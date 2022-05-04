#include "CrossRoad_Map.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/MapManager.hpp"

void CrossRoad_Map::Init()
{
	textureBG.loadFromFile("Resources/Sprite/UI/Area_Forgotten Crossroads.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setPosition(990.f, 820.f);
	spriteBG.setOrigin(spriteBG.getLocalBounds().width / 2, spriteBG.getLocalBounds().height / 2);

}

void CrossRoad_Map::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Space))
	{
		MapManager::GetInstance().LoadMap(MAP_TYPE::Town);
	}
}

void CrossRoad_Map::Render(sf::RenderWindow& window)
{
	window.draw(spriteBG);
}

void CrossRoad_Map::Release()
{
}
