#include "ManagerTestScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"

ManagerTestScene::ManagerTestScene() noexcept
{
}

ManagerTestScene::~ManagerTestScene() noexcept
{
}

void ManagerTestScene::Init()
{
	textureBG = TextureManager::GetInstance().GetTexture("Resources/Sprite/controller_prompt_bg.png");
	spriteBG.setTexture(textureBG);
	spriteBG.setOrigin(textureBG.getSize().x * 0.5f, textureBG.getSize().y * 0.5f);
	spriteBG.setPosition(ViewManager::GetInstance().GetResolution().x * 0.5f, ViewManager::GetInstance().GetResolution().y * 0.5f);
}

void ManagerTestScene::Update(float dt)
{
}

void ManagerTestScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteBG);
}

void ManagerTestScene::Release()
{
}
