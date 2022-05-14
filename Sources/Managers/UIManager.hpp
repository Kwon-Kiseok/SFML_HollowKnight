#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "SceneManager.hpp"
#include "../include/Singleton.hpp"
#include "../Scene/InventoryScene.hpp"
#include "../Items/Coin.hpp"
#include "../Player/Player.hpp"
#include "../Utils/button.hpp"
#include "../UI/PauseUI.hpp"

using namespace sf;

class UIManager : public Singleton<UIManager>
{
private:
	Texture textureMouseCursor;
	Sprite spriteMouseCursor;

	Texture textureBackGround;
	Sprite spriteBackGround;

	Texture textureTitle;
	Sprite spriteTitle;

	Font fontCALIST;

	std::unordered_map<wstring, button*> titleButtons;
	wstring currentSelectButtonID;
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

	// 맵
	bool mapVisible = false;
	InventoryScene inventory;

	// 일시정지
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
	void Release_TitleScene();
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

	// 일시정지 UI
	void Init_Pause();
	void Update_Pause(float dt);
	void Render_Pause(sf::RenderWindow& window);
	void Release_Pause();
};

