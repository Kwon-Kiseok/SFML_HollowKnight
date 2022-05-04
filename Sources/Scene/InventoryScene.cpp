#include "InventoryScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"

void InventoryScene::Init()
{
	textureBackUI = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/credits vignette.png");
	spriteBackUI.setTexture(textureBackUI);
	spriteBackUI.setPosition(0, 0);

	textureFrameLT = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/overscan_corner_fleur009.png");
	spriteFrameLT.setTexture(textureFrameLT);
	spriteFrameLT.setPosition(50, 70);

	textureFrameCT = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/prompt_divider.png");
	spriteFrameCT.setTexture(textureFrameCT);
	spriteFrameCT.setPosition(450, 100);

	textureFrameRT = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/overscan_corner_fleur009.png");
	spriteFrameRT.setTexture(textureFrameRT);
	spriteFrameRT.scale(-1.f, 1.f);
	spriteFrameRT.setPosition(1870, 70);

	textureFrameLB = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/overscan_corner_fleur009.png");
	spriteFrameLB.setTexture(textureFrameLB);
	spriteFrameLB.scale(1.f, -1.f);
	spriteFrameLB.setPosition(50, 1010);

	textureFrameCB = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/Yes_No_bottom_fleur0007.png");
	spriteFrameCB.setTexture(textureFrameCB);
	spriteFrameCB.setPosition(775, 950);

	textureFrameRB = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/overscan_corner_fleur009.png");
	spriteFrameRB.setTexture(textureFrameRB);
	spriteFrameRB.scale(-1.f, -1.f);
	spriteFrameRB.setPosition(1870, 1010);

	fontCALIST.loadFromFile("Resources/Fonts/CALIST.ttf");

	textInven.setFont(fontCALIST);
	textInven.setString("Inventory");
	textInven.setCharacterSize(35);
	textInven.setFillColor(Color::White);
	textInven.setPosition(900, 50);
}

void InventoryScene::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::I))
	{
		visible = !visible;
	}
}

void InventoryScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteBackUI);
	window.draw(spriteFrameLT);
	window.draw(spriteFrameCT);
	window.draw(spriteFrameRT);
	window.draw(spriteFrameLB);
	window.draw(spriteFrameCB);
	window.draw(spriteFrameRB);
	
	window.draw(textInven);
}

void InventoryScene::Release()
{
}

void InventoryScene::SetVisible(bool is)
{
	visible = is;
}

bool InventoryScene::GetVisible()
{
	return visible;
}
