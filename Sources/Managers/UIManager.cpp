#include "UIManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../Items/Coin.hpp"

#include <sstream>

void UIManager::Init()
{
}

void UIManager::Update(float dt)
{
}

void UIManager::Render(sf::RenderWindow& window)
{
}

void UIManager::Release()
{
}

void UIManager::Init_TitleScene()
{
	//std::cout << "TitleScene Load" << std::endl;
	textureBackGround = TextureManager::GetInstance().GetTexture("Resources/Sprite/Voidheart_menu_BG.png");
	spriteBackGround.setTexture(textureBackGround);
	spriteBackGround.setOrigin(textureBackGround.getSize().x, textureBackGround.getSize().y);
	spriteBackGround.setPosition(ViewManager::GetInstance().GetResolution().x * 1.f, ViewManager::GetInstance().GetResolution().y * 1.25f);

	textureTitle = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/title.png");
	spriteTitle.setTexture(textureTitle);
	spriteTitle.setOrigin(textureTitle.getSize().x, textureTitle.getSize().y);
	spriteTitle.setPosition(ViewManager::GetInstance().GetResolution().x * 0.8f, ViewManager::GetInstance().GetResolution().y * 0.5f);

	textureCursor = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/main_menu_pointer.png");
	spriteCursor.setTexture(textureCursor);
	spriteCursor.scale(-1.f, 1.f);

	spriteCursor.setPosition(1920 * 0.5f, Cursor_selectY);

	fontCALIST.loadFromFile("Resources/Fonts/CALIST.ttf");

	textPlay.setFont(fontCALIST);
	textPlay.setString("Game Start");
	textPlay.setCharacterSize(80);
	textPlay.setFillColor(Color::White);
	textPlay.setPosition(1920 * 0.5f, 600.f);

	textEditor.setFont(fontCALIST);
	textEditor.setString("Editor Mode");
	textEditor.setCharacterSize(80);
	textEditor.setFillColor(Color::White);
	textEditor.setPosition(1920 * 0.5f, 750.f);

	textExit.setFont(fontCALIST);
	textExit.setString("Exit");
	textExit.setCharacterSize(80);
	textExit.setFillColor(Color::White);
	textExit.setPosition(1920 * 0.5f, 900.f);

	SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/Title.wav");
}

void UIManager::Update_TitleScene(float dt)
{
	spriteCursor.setPosition(1920 * 0.5f, Cursor_selectY);

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Up))
	{
		SoundManager::GetInstance().PlaySound(L"changeMenu");

		Cursor_selectY -= 150;
		if (Cursor_selectY < 600.f)
		{
			Cursor_selectY = 900.f;
		}
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Down))
	{
		SoundManager::GetInstance().PlaySound(L"changeMenu");

		Cursor_selectY += 150;
		if (Cursor_selectY > 900.f)
		{
			Cursor_selectY = 600.f;
		}
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Enter))
	{
		if (Cursor_selectY == 600.f)
		{
			SceneManager::GetInstance().Load(L"Play");
 			SoundManager::GetInstance().StopMusic();
		}
		else if (Cursor_selectY == 750.f)
		{
			SceneManager::GetInstance().Load(L"Editor");
		}
		else if (Cursor_selectY == 900.f)
		{
			
		}
		SoundManager::GetInstance().PlaySound(L"select");
	}

	if (textPlay.getGlobalBounds().contains(InputManager::GetInstance().GetMouseWorldPosition()))
	{
		Cursor_selectY = 600.f;

		if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
		{
			SceneManager::GetInstance().Load(L"Play");
			SoundManager::GetInstance().StopMusic();
		}
	}
	if (textEditor.getGlobalBounds().contains(InputManager::GetInstance().GetMouseWorldPosition()))
	{
		Cursor_selectY = 750.f;

		if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
		{
			SceneManager::GetInstance().Load(L"Editor");
		}
	}
	if (textExit.getGlobalBounds().contains(InputManager::GetInstance().GetMouseWorldPosition()))
	{
		Cursor_selectY = 900.f;

		if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
		{
			
		}
	}
}

void UIManager::Render_TitleScene(sf::RenderWindow& window)
{
	window.draw(spriteBackGround);
	window.draw(spriteTitle);
	window.draw(textPlay);
	window.draw(textEditor);
	window.draw(textExit);
	window.draw(spriteCursor);
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

}

void UIManager::Update_PlayScene(float dt)
{
	stringstream ssCoin;
	ssCoin << PlayerDataManager::GetInstance().GetPlayerCoin();
	textCoin.setString(ssCoin.str());

	inventory.Update(dt);
	Update_Map(dt);

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

