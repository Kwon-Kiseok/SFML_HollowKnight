#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include "../include/Singleton.hpp"
#include "../Scene/InventoryScene.hpp"
#include <vector>
#include "../Items/Coin.hpp"
#include "../Player/Player.hpp"
#include "../UI/PauseUI.hpp"

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

	Texture* textureNoLife;
	Sprite* spriteNoLife;

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

	// ��
	bool mapVisible = false;
	InventoryScene inventory;

	// �Ͻ�����
	PauseUI pauseUI;
	bool isPauseMenu = false;

public:
	virtual ~UIManager() override;
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
	bool GetIsPause();
	void SetIsPause(bool is);

	// �Ͻ����� UI
	void Init_Pause();
	void Update_Pause(float dt);
	void Render_Pause(sf::RenderWindow& window);
	void Release_Pause();
};

