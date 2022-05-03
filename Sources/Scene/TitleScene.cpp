#include "TitleScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include <iostream>

void TitleScene::Init()
{
	//std::cout << "TitleScene Load" << std::endl;
	textureBG = TextureManager::GetInstance().GetTexture("Resources/Sprite/Voidheart_menu_BG.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setOrigin(textureBG.getSize().x, textureBG.getSize().y);
	spriteBG.setPosition(ViewManager::GetInstance().GetResolution().x * 1.f, ViewManager::GetInstance().GetResolution().y * 1.25f);

	textureBeamEffect = TextureManager::GetInstance().GetTexture("Resources/Sprite/Main_Menu_Beam.png");
	spriteBeamEffect.setTexture(textureBeamEffect);
	spriteBeamEffect.setOrigin(textureBeamEffect.getSize().x, textureBeamEffect.getSize().y);
	spriteBeamEffect.setPosition(ViewManager::GetInstance().GetResolution().x * 1.f, ViewManager::GetInstance().GetResolution().y * 1.5f);

	textureTitle = TextureManager::GetInstance().GetTexture("Resources/Sprite/title.png");
	spriteTitle.setTexture(textureTitle);
	spriteTitle.setOrigin(textureTitle.getSize().x, textureTitle.getSize().y);
	spriteTitle.setPosition(ViewManager::GetInstance().GetResolution().x * 0.8f, ViewManager::GetInstance().GetResolution().y * 0.5f);
}


void TitleScene::Update(float dt)
{

}

void TitleScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteBG);
	window.draw(spriteTitle);
	window.draw(spriteBeamEffect);

}

void TitleScene::Release()
{
}
