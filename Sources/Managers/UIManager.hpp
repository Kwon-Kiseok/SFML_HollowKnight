#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include "../include/Singleton.hpp"
#include "../Scene/InventoryScene.hpp"
#include <vector>
#include "../Items/Coin.hpp"

using namespace sf;

class UIManager : public Singleton<UIManager>
{
private:
	float Cursor_selectY = 600.f;
	Coin coin;

	Texture textureBackGround;
	Sprite spriteBackGround;

	Texture textureTitle;
	Sprite spriteTitle;

	Texture textureCursor;
	Sprite spriteCursor;

	Font fontCALIST;
	Text textPlay;
	Text textEditor;
	Text textExit;
////////////////////////////////////////////////

	Texture* textureLifes;
	Sprite* spriteLifes;

	Texture* textureNoLife;
	Sprite* spriteNoLife;

	int currentHP = 5;

	Texture textureCharacterUI;
	Sprite spriteCharacterUI;

	Texture textureCoin;
	Sprite spriteCoin;

	Text textCoin;
// /////////////////////////////////////////////

	Texture textureTown;
	Sprite spriteTown;

	Texture textureBack;
	Sprite spriteBack;


	bool mapVisible = false;
	InventoryScene inventory;

public:
	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow& window);
	void Release();

	void Init_TitleScene();
	void Update_TitleScene(float dt);
	void Render_TitleScene(sf::RenderWindow& window);
// /////////////////////////////////////////////////////////////

	void Init_PlayScene();
	void Update_PlayScene(float dt);
	void Render_PlayScene(sf::RenderWindow& window);
	void Release_PlayScene();

// /////////////////////////////////////////////////////////////

	void Init_Map();
	void Update_Map(float dt);
	void Render_Map(sf::RenderWindow& window);
	void SetMapVisible(bool map);
	bool GetMapVisible();
	

	bool GetMapIsOpen();
	bool GetInventoryIsOpen();
};

