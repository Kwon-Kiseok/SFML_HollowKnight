#include "PlayScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"

void PlayScene::Init()
{
	textureLife1 = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
	spriteLife1.setTexture(textureLife1);
	spriteLife1.setPosition(250, 80);

	textureLife2 = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
	spriteLife2.setTexture(textureLife2);
	spriteLife2.setPosition(300, 80);

	textureLife3 = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
	spriteLife3.setTexture(textureLife3);
	spriteLife3.setPosition(350, 80);

	textureLife4 = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
	spriteLife4.setTexture(textureLife4);
	spriteLife4.setPosition(400, 80);

	textureLife5= TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
	spriteLife5.setTexture(textureLife5);
	spriteLife5.setPosition(450, 80);


	textureCharacterUI = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0002_health_frame2.png");
	spriteCharacterUI.setTexture(textureCharacterUI);
	spriteCharacterUI.setPosition(30, 30);

	textureCoin = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_coin_v020004.png");
	spriteCoin.setTexture(textureCoin);
	spriteCoin.setPosition(200, 150);


	fontCALIST.loadFromFile("Resources/Fonts/CALIST.ttf");
	textCoin.setString("200");
	textCoin.setPosition(270, 160);
	textCoin.setCharacterSize(35);
	textCoin.setFillColor(Color::White);

	player = new Player();
	player->Init();

	tile = new DemoTile(740, 900);
	textCoin.setFont(fontCALIST);
}

void PlayScene::Update(float dt)
{
	player->Update(dt, tile->GetGlobalBounds());
}

void PlayScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteCharacterUI);
	window.draw(spriteCoin);
	player->Draw(window);


	window.draw(tile->GetShape());

	window.draw(spriteLife1);
	window.draw(spriteLife2);
	window.draw(spriteLife3);
	window.draw(spriteLife4);
	window.draw(spriteLife5);
}

void PlayScene::Release()
{
	delete player;
	delete tile;
}
