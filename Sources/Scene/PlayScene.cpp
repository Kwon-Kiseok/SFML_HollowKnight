#include "PlayScene.h"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"

void PlayScene::Init()
{
	textureCharacterUI = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0002_health_frame2.png");
	spriteCharacterUI.setTexture(textureCharacterUI);
	spriteCharacterUI.setPosition(30, 30);

	textureCoin = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_coin_v020004.png");
	spriteCoin.setTexture(textureCoin);
	spriteCoin.setPosition(200, 150);

	textureLife = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
	
	const int countLife = 5;
	Sprite spriteLife[countLife];
	for (int i = 0; i < countLife; i++)
	{
		spriteLife[i].setTexture(textureLife);
		spriteLife[i].setPosition(200 + i * 20, 150);
	}


	fontArial.loadFromFile("Resources/Sprite/arial.ttf");
	textCoin.setString("200");
	textCoin.setPosition(270, 160);
	textCoin.setCharacterSize(35);
	textCoin.setFillColor(Color::White);
	//textCoin.setFont(fontArial);

	player = new Player();
	player->Init();

	tile = new DemoTile(740, 900);
}

void PlayScene::Update(float dt)
{
	player->Update(dt, tile->GetGlobalBounds());
}

void PlayScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteCharacterUI);
	window.draw(spriteLife);
	window.draw(spriteCoin);
	player->Draw(window);
	//window.draw(textCoin);

	/*for (int i = 0; i < countLife; i++)
	{
		window.draw(spriteLife[i]);
	}*/
	window.draw(tile->GetShape());
}

void PlayScene::Release()
{
	delete player;
	delete tile;
}
