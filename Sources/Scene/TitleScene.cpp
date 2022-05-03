#include "TitleScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include <iostream>


void TitleScene::Init()
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
	
	fontArial.loadFromFile("Resources/Sprite/arial.ttf");

	textPlay.setFont(fontArial);
	textPlay.setString("Game Start");
	textPlay.setCharacterSize(80);
	textPlay.setFillColor(Color::White);
	textPlay.setPosition(1920 * 0.5f, 600.f);

	textEditor.setFont(fontArial);
	textEditor.setString("Editor Mode");
	textEditor.setCharacterSize(80);
	textEditor.setFillColor(Color::White);
	textEditor.setPosition(1920 * 0.5f, 750.f);

	textExit.setFont(fontArial);
	textExit.setString("Exit");
	textExit.setCharacterSize(80);
	textExit.setFillColor(Color::White);
	textExit.setPosition(1920 * 0.5f, 900.f);

	SoundManager::GetInstance().PlayMusic("Resources/AudioClip/BGM/Title.wav");
}


void TitleScene::Update(float dt)
{
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Up))
	{
		Cursor_selectY -= 150;
		if (Cursor_selectY < 600.f)
		{
			Cursor_selectY = 900.f;
		}
		spriteCursor.setPosition(1920 * 0.5f, Cursor_selectY);
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Down))
	{
		Cursor_selectY += 150;
		if (Cursor_selectY > 900.f)
		{
			Cursor_selectY = 600.f;
		}
		spriteCursor.setPosition(1920 * 0.5f, Cursor_selectY);
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Enter))
	{
		if (Cursor_selectY == 600.f)
		{
			SceneManager::GetInstance().Load(L"PLAY");
		}
		else if (Cursor_selectY == 750.f)
		{
			SceneManager::GetInstance().Load(L"Editor");
		}
		else if (Cursor_selectY == 900.f)
		{
			SceneManager::GetInstance().Load(L"Exit");
		}

	}
}

void TitleScene::Render(sf::RenderWindow& window)
{
	window.draw(spriteBackGround);
	window.draw(spriteTitle);
	window.draw(textPlay);
	window.draw(textEditor);
	window.draw(textExit);
	window.draw(spriteCursor);
}

void TitleScene::Release()
{
}
