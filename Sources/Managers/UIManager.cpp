#include "UIManager.hpp"
#include "../Framework/Game.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../Items/Coin.hpp"

#include <sstream>

UIManager::~UIManager()
{
	Release();
}

void UIManager::Init()
{
	textureMouseCursor.loadFromFile("Resources/Sprite/UI/Cursor.png");
	spriteMouseCursor.setTexture(textureMouseCursor);
}

void UIManager::Update(float dt)
{
	spriteMouseCursor.setPosition(static_cast<Vector2f>(InputManager::GetInstance().GetMousePosition()));
}

void UIManager::Render(sf::RenderWindow& window)
{
	window.draw(spriteMouseCursor);
}

void UIManager::Release()
{
	Release_Pause();
	Release_TitleScene();
}

void UIManager::Init_TitleScene()
{
	float resolution_x = ViewManager::GetInstance().GetResolution().x;
	float resolution_y = ViewManager::GetInstance().GetResolution().y;

	textureBackGround = TextureManager::GetInstance().GetTexture("Resources/Sprite/Voidheart_menu_BG.png");
	spriteBackGround.setTexture(textureBackGround);
	spriteBackGround.setOrigin(textureBackGround.getSize().x/2, textureBackGround.getSize().y/2);
	spriteBackGround.setPosition(resolution_x/2, resolution_y /2);

	textureTitle = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/title.png");
	spriteTitle.setTexture(textureTitle);
	spriteTitle.setOrigin(textureTitle.getSize().x/2, textureTitle.getSize().y/2);
	spriteTitle.setPosition(resolution_x /2, resolution_y /2 - 200.f);

	fontCALIST.loadFromFile("Resources/Fonts/CALIST.ttf");

	titleButtons[L"gameStart"] = new button("Game Start", Vector2f(resolution_x / 2.f, resolution_y / 2.f + 100.f), Vector2f(200.f, 40.f));
	titleButtons[L"editorMode"] = new button("Editor Mode", Vector2f(resolution_x / 2.f, resolution_y / 2.f + 200.f), Vector2f(200.f, 40.f));
	titleButtons[L"exit"] = new button("Exit", Vector2f(resolution_x / 2.f, resolution_y / 2.f + 300.f), Vector2f(200.f, 40.f));

	titleButtons[L"gameStart"]->Select(true);
	currentSelectButtonID = L"gameStart";
	SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/Title.wav");
}

void UIManager::Update_TitleScene(float dt)
{
	titleButtons[currentSelectButtonID]->Select(true);

	for (auto& button : titleButtons)
	{
		button.second->update(dt);

		if (InputManager::GetInstance().GetKeyDown(Keyboard::Up) && (button.second->IsButtonSelect()))
		{
			if (currentSelectButtonID == "gameStart")
			{
				button.second->Select(false);
				currentSelectButtonID = L"exit";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
			else if (currentSelectButtonID == "editorMode")
			{
				button.second->Select(false);
				currentSelectButtonID = L"gameStart";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
			else if (currentSelectButtonID == "exit")
			{
				button.second->Select(false);
				currentSelectButtonID = L"editorMode";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
		}
		else if (InputManager::GetInstance().GetKeyDown(Keyboard::Down) && (button.second->IsButtonSelect()))
		{
			if (currentSelectButtonID == "gameStart")
			{
				button.second->Select(false);
				currentSelectButtonID = L"editorMode";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
			else if (currentSelectButtonID == "editorMode")
			{
				button.second->Select(false);
				currentSelectButtonID = L"exit";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
			else if (currentSelectButtonID == "exit")
			{
				button.second->Select(false);
				currentSelectButtonID = L"gameStart";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
		}
		else if (InputManager::GetInstance().GetKeyDown(Keyboard::Enter) && (button.second->IsButtonSelect()))
		{
			if (currentSelectButtonID == "gameStart")
			{
				SceneManager::GetInstance().Load(L"Play");
				SoundManager::GetInstance().StopMusic();
			}
			else if (currentSelectButtonID == "editorMode")
			{
				SceneManager::GetInstance().Load(L"Editor");
				SoundManager::GetInstance().StopMusic();
			}
			else if (currentSelectButtonID == "exit")
			{
				Game::GetInstance().SetIsGameOver(true);
				SoundManager::GetInstance().StopMusic();
			}
		}

		for (auto check : titleButtons)
		{
			if (check.second->IsButtonSelect())
			{
				if (check.first != currentSelectButtonID)
				{
					titleButtons[currentSelectButtonID]->Select(false);

					currentSelectButtonID = check.first;
				}
			}
		}
	}

	if (titleButtons[L"gameStart"]->IsButtonClicked())
	{
		SceneManager::GetInstance().Load(L"Play");
		SoundManager::GetInstance().StopMusic();
		titleButtons[L"gameStart"]->ResetIsClicked();
	}
	if (titleButtons[L"editorMode"]->IsButtonClicked())
	{
		SceneManager::GetInstance().Load(L"Editor");
		SoundManager::GetInstance().StopMusic();
		titleButtons[L"editorMode"]->ResetIsClicked();
	}
	if (titleButtons[L"exit"]->IsButtonClicked())
	{
		SoundManager::GetInstance().StopMusic();
		Game::GetInstance().SetIsGameOver(true);
		titleButtons[L"exit"]->ResetIsClicked();
	}
}

void UIManager::Render_TitleScene(sf::RenderWindow& window)
{
	window.draw(spriteBackGround);
	window.draw(spriteTitle);
	for (auto& button : titleButtons)
	{
		button.second->draw(window);
	}
}

void UIManager::Release_TitleScene()
{
	for (auto& button : titleButtons)
	{
		delete button.second;
	}
	titleButtons.clear();
}

/////////////////////////////////////////////////////////////////////////

void UIManager::Init_PlayScene()
{
	textureLifes = new Texture[5];
	spriteLifes = new Sprite[5];

	for (int i = 0; i < 5; i++)
	{
		textureLifes[i] = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health.png");
		spriteLifes[i].setTexture(textureLifes[i]);
		spriteLifes[i].setPosition(250 + 50 * i, 80);
	}

	textureNoLife = new Texture[5];
	spriteNoLife = new Sprite[5];

	for (int i = 0; i < 5; i++)
	{
		textureNoLife[i] = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0001_health_steel.png");
		spriteNoLife[i].setTexture(textureNoLife[i]);
		spriteNoLife[i].setPosition(450 - 50 * i, 80);
	}

	textureCharacterUI = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_0002_health_frame2.png");
	spriteCharacterUI.setTexture(textureCharacterUI);
	spriteCharacterUI.setPosition(30, 30);

	textureCoin = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/select_game_HUD_coin_v020004.png");
	spriteCoin.setTexture(textureCoin);
	spriteCoin.setPosition(210, 150);

	fontCALIST.loadFromFile("Resources/Fonts/CALIST.ttf");

	stringstream ssCoin;
	ssCoin << PlayerDataManager::GetInstance().GetPlayerHP();
	textCoin.setString(ssCoin.str());
	textCoin.setPosition(275, 153);
	textCoin.setCharacterSize(40);
	textCoin.setFillColor(Color::White);
	textCoin.setFont(fontCALIST);

	inventory.Init();
	Init_Map();
	Init_Pause();

}

void UIManager::Update_PlayScene(float dt)
{
	stringstream ssCoin;
	ssCoin << PlayerDataManager::GetInstance().GetPlayerCoin();
	textCoin.setString(ssCoin.str());

	inventory.Update(dt);
	Update_Map(dt);
	Update_Pause(dt);
}

void UIManager::Render_PlayScene(sf::RenderWindow& window)
{
	window.setView(ViewManager::GetInstance().GetUiView());
	ViewManager::GetInstance().draw(window);
	window.draw(spriteCharacterUI);
	window.draw(spriteCoin);
	window.draw(textCoin);

	for (int i = 0; i < 5; i++)
	{
		window.draw(spriteNoLife[i]);
	}

	for (int i = 0; i < PlayerDataManager::GetInstance().GetPlayerHP(); i++)
	{
		window.draw(spriteLifes[i]);
	}

	if (inventory.GetVisible())
		inventory.Render(window);

	if (GetMapVisible() && !inventory.GetVisible())
		Render_Map(window);

	if (isPauseMenu)
		Render_Pause(window);
}

void UIManager::Release_PlayScene()
{
	delete[] textureLifes;
	delete[] spriteLifes;
	delete[] textureNoLife;
	delete[] spriteNoLife;

	textureLifes = nullptr;
	spriteLifes = nullptr;
	textureNoLife = nullptr;
	spriteNoLife = nullptr;

}

// //////////////////////////////////////////////////////////////////////

void UIManager::Init_Map()
{
	textureTown = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/map/SpriteTown.png");
	spriteTown.setTexture(textureTown);
	spriteTown.setPosition(660, 440);

	textureBack = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/map/back.png");
	spriteBack.setTexture(textureBack);
	spriteBack.setPosition(0, 0);
}

void UIManager::Update_Map(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Tab))
	{
		mapVisible = !mapVisible;
	}
}

void UIManager::Render_Map(sf::RenderWindow& window)
{
	window.draw(spriteBack);
	window.draw(spriteTown);
}

void UIManager::SetMapVisible(bool open)
{
	mapVisible = open;
}

bool UIManager::GetMapVisible()
{
	return mapVisible;
}

bool UIManager::GetMapIsOpen()
{
	return GetMapVisible();
}

bool UIManager::GetInventoryIsOpen()
{
	return inventory.GetVisible();
}

bool UIManager::GetIsPause()
{
	return isPauseMenu;
}

void UIManager::SetIsPause(bool is)
{
	isPauseMenu = is;
}

void UIManager::Init_Pause()
{
	pauseUI.Init();
}

void UIManager::Update_Pause(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Escape))
	{
		isPauseMenu = !isPauseMenu;
		pauseUI.GetAnim().Play("Top_fleur");
	}

	if (isPauseMenu)
	{
		pauseUI.Update(dt);
	}
}

void UIManager::Render_Pause(sf::RenderWindow& window)
{
	window.draw(spriteBack);

	if (isPauseMenu)
	{
		pauseUI.Render(window);
	}
}

void UIManager::Release_Pause()
{
	pauseUI.Release();
}

