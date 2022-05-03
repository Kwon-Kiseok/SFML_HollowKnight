#include "ManagerTestScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/InputManager.hpp"

ManagerTestScene::ManagerTestScene() noexcept
{
}

ManagerTestScene::~ManagerTestScene() noexcept
{
}

void ManagerTestScene::Init()
{
	textureBG = TextureManager::GetInstance().GetTexture("Resources/Sprite/Voidheart_menu_BG.png");
	spriteBG.setTexture(textureBG);

	spriteBG.setOrigin(textureBG.getSize().x * 0.5f, textureBG.getSize().y * 0.5f);
	spriteBG.setPosition(ViewManager::GetInstance().GetResolution().x * 0.5f, ViewManager::GetInstance().GetResolution().y * 0.5f);

	textureVignette = TextureManager::GetInstance().GetTexture("Resources/Sprite/controller_dialogue_vignette.png");
	spriteVignette.setTexture(textureVignette);
	spriteVignette.setOrigin(textureVignette.getSize().x * 0.5f, textureVignette.getSize().y * 0.5f);
	spriteVignette.setPosition(ViewManager::GetInstance().GetResolution().x * 0.5f, ViewManager::GetInstance().GetResolution().y * 0.5f - 22.f);

	SoundManager::GetInstance().AddSound("Resources/AudioClip/sword_1.wav", L"SWORD_1");
	SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/Title.wav");
}

void ManagerTestScene::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(sf::Keyboard::Space))
	{
		SoundManager::GetInstance().PlaySound(L"SWORD_1");
	}
}

void ManagerTestScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteBG);
	window.draw(spriteVignette);
}

void ManagerTestScene::Release()
{
}
