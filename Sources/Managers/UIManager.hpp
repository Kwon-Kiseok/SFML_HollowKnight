#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include "../include/Singleton.hpp"
#include <vector>

using namespace sf;

class UIManager : public Singleton<UIManager>
{
private:
	float Cursor_selectY = 600.f;

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

	Texture textureCharacterUI;
	Sprite spriteCharacterUI;

	Texture textureCoin;
	Sprite spriteCoin;

	Font fontCALIST;
	Text textCoin;

public:
	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow& window);
	void Release();

	void Init_TitleScene();
	void Update_TitleScene(float dt);
	void Render_TitleScene(sf::RenderWindow& window);

	void Init_PlayScene();
	void Update_PlayScene(float dt);
	void Render_PlayScene(sf::RenderWindow& window);
	void Release_PlayScene();


};

