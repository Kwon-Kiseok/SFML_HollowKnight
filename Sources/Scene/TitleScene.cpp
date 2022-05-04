#include "TitleScene.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/UIManager.hpp"
#include <iostream>


void TitleScene::Init()
{
	UIManager::GetInstance().Init_TitleScene();
}


void TitleScene::Update(float dt)
{
	//UIManager::GetInstance().Update_TitleScene(dt);
	spriteCursor.setPosition(1920 * 0.5f, Cursor_selectY);
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Up))
	{
		Cursor_selectY -= 150;
		if (Cursor_selectY < 600.f)
		{
			Cursor_selectY = 900.f;
		}
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Down))
	{
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

	if (textPlay.getGlobalBounds().contains(InputManager::GetInstance().GetMouseWorldPosition()))
	{
		Cursor_selectY = 600.f;
	}
}

void TitleScene::Render(sf::RenderWindow& window)
{
	//UIManager::GetInstance().Render_TitleScene(window);
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
