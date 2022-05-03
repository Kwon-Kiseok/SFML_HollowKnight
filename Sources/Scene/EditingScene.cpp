#include "EditingScene.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/InputManager.hpp"

#include <iostream>

void EditingScene::Init()
{
	textureLoadButton = new button("Texture", Vector2f(1850.f, 200.f), Vector2f(100.f, 25.f));
	isOpenTextureWindow = false;
	listBoxUI = new textureListBoxUI();
	clickCount = 0;
}

void EditingScene::Update(float dt)
{
	textureLoadButton->update();
	if (textureLoadButton->IsButtonClicked())
	{
		isOpenTextureWindow = true;
	}
	listBoxUI->Update(&isOpenTextureWindow);

	if (listBoxUI->GetIsDrop())
	{
		Texture* tex = new Texture();
		Sprite* spr = new Sprite();

		if(listBoxUI->GetId() == "rock")
			tex->loadFromFile("Resources/Sprite/BG/Tutorial/tut_edge_02_0001_03.png");
		else if(listBoxUI->GetId() == "pole")
			tex->loadFromFile("Resources/Sprite/BG/Tutorial/tutorial_poles_0008_a.png");
		spr->setTexture(*tex);

		spr->setPosition(listBoxUI->GetDropImage().getPosition());
		spr->setOrigin(listBoxUI->GetDropImage().getOrigin());

		textureMap.insert(make_pair("Temp", tex));
		spriteMap.insert(make_pair(clickCount++, spr));

		listBoxUI->ResetIsDrop();
	}
}

void EditingScene::Render(sf::RenderWindow& window)
{
	textureLoadButton->draw(window);
	if (isOpenTextureWindow)
	{
		listBoxUI->Render(window);
	}

	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it)
	{
		window.draw(*it->second);
	}
}

void EditingScene::Release()
{
	delete textureLoadButton;
	listBoxUI->Release();

	for (auto it = textureMap.begin(); it != textureMap.end(); ++it)
	{
		delete it->second;
	}
	textureMap.clear();

	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it)
	{
		std::cout << it->first << ": " << it->second->getPosition().x << ", " << it->second->getPosition().y << std::endl;

		delete it->second;
	}
	spriteMap.clear();
}
