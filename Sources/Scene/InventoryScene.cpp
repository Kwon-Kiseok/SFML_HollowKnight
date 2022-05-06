#include "InventoryScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/UIManager.hpp"
#include <sstream>

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
	textInven.setPosition(883, 50);


	textureHealth = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/Inv_0030_inv_health_backboard.png");
	spriteHealth.setTexture(textureHealth);
	spriteHealth.setPosition(150, 150);

	textureSoul = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/Inv_0032_inv_soul_backboard.png");
	spriteSoul.setTexture(textureSoul);
	spriteSoul.setPosition(400, 240);

	textureSpellCore = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/Inv_0029_spell_core.png");
	spriteSpellCore.setTexture(textureSpellCore);
	spriteSpellCore.setPosition(365, 550);

	textureNail = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/Inv_0033_inv_nail_01.png");
	spriteNail.setTexture(textureNail);
	spriteNail.setPosition(180, 450);

	textureInvenCoin = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/InventoryCoin.png");
	spriteInvenCoin.setTexture(textureInvenCoin);
	spriteInvenCoin.setPosition(350, 900);
}

void InventoryScene::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::I))
	{
		visible = !visible;
	}

	stringstream ssCoin;
	ssCoin << coin.GetCoin();
	textCoin.setString(ssCoin.str());
	textCoin.setPosition(430, 910);
	textCoin.setCharacterSize(40);
	textCoin.setFillColor(Color::White);
	textCoin.setFont(fontCALIST);

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

	window.draw(spriteHealth);
	window.draw(spriteSoul);
	window.draw(spriteSpellCore);
	window.draw(spriteNail);

	window.draw(spriteInvenCoin);
	window.draw(textCoin);
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
