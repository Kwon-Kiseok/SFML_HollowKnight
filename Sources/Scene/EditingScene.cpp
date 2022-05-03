#include "EditingScene.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/InputManager.hpp"

void EditingScene::Init()
{
	textureLoadButton = new button("Texture", Vector2f(1850.f, 200.f), Vector2f(100.f, 25.f));
	isOpenTextureWindow = false;
	listBoxUI = new textureListBoxUI();
}

void EditingScene::Update(float dt)
{
	textureLoadButton->update();
	if (textureLoadButton->IsButtonClicked())
	{
		isOpenTextureWindow = true;
	}
	listBoxUI->Update(&isOpenTextureWindow);
}

void EditingScene::Render(sf::RenderWindow& window)
{
	textureLoadButton->draw(window);
	if (isOpenTextureWindow)
	{
		listBoxUI->Render(window);
	}
}

void EditingScene::Release()
{
	delete textureLoadButton;
	listBoxUI->Release();
}
