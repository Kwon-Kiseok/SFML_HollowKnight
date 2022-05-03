#include "textureListBoxUI.hpp"
#include "../Managers/InputManager.hpp"

#include <iostream>

textureListBoxUI::textureListBoxUI()
{
	isActive = false;
	isDrop = false;

	ListBox.setSize(Vector2f(700.f, 500.f));
	ListBox.setOrigin(ListBox.getGlobalBounds().width / 2, ListBox.getGlobalBounds().height / 2);
	ListBox.setPosition(1920.f * 0.5f, 1080.f * 0.5f);
	ListBox.setFillColor(Color::White);

	closeButton = new button("Close", Vector2f(ListBox.getPosition().x, ListBox.getPosition().y + (ListBox.getGlobalBounds().height / 2) - 20.f), Vector2f(80.f, 25.f));

	testRockButton = new button("rock", Vector2f(ListBox.getLocalBounds().width / 2, ListBox.getLocalBounds().height / 2), Vector2f(80.f, 40.f));

	testPoleButton = new button("pole", Vector2f(ListBox.getLocalBounds().width / 2 + 100.f, ListBox.getLocalBounds().height / 2), Vector2f(80.f, 40.f));

}

textureListBoxUI::~textureListBoxUI()
{
}

void textureListBoxUI::Init()
{
}

void textureListBoxUI::AddTexture(string path, string id, Vector2f pos)
{
	texture.loadFromFile(path);
	Sprite* sprite = new Sprite();
	sprite->setTexture(texture);

	sprite->setPosition(pos);
	sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);

	spriteMap.insert(make_pair(id, sprite));
}

void textureListBoxUI::Update(bool* isOpen)
{
	// 텍스처 윈도우 창이 열려있을 때만
	if (*isOpen)
	{
		// 클로즈 버튼 활성화
		closeButton->update();
		testRockButton->update();
		testPoleButton->update();
	}
	if (closeButton->IsButtonClicked())
	{
		*isOpen = false;
		closeButton->ResetIsClicked();
	}

	//
	if (testRockButton->IsButtonClicked())
	{
		id = "rock";
		AddTexture("Resources/Sprite/BG/Tutorial/tut_edge_02_0001_03.png", id, InputManager::GetInstance().GetMouseWorldPosition());
		isActive = true;
	}
	else if (testPoleButton->IsButtonClicked())
	{
		id = "pole";
		AddTexture("Resources/Sprite/BG/Tutorial/tutorial_poles_0008_a.png", id, InputManager::GetInstance().GetMouseWorldPosition());
		isActive = true;
	}
	else if (isActive)
	{

		spriteMap.find(id)->second->setPosition(InputManager::GetInstance().GetMouseWorldPosition());

		if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
		{
			std::cout << spriteMap.find(id)->second->getPosition().x << ", " << spriteMap.find(id)->second->getPosition().y << std::endl;
			
			isActive = false;
			isDrop = true;
		}
	}

}

void textureListBoxUI::Render(RenderWindow& window)
{
	window.draw(ListBox);
	closeButton->draw(window);
	testRockButton->draw(window);
	testPoleButton->draw(window);

	if (isActive)
	{
		for (auto& it : spriteMap)
		{
			window.draw(*it.second);
		}
	}
}

void textureListBoxUI::Release()
{
	delete closeButton;

}

Sprite& textureListBoxUI::GetDropImage()
{
	auto it = spriteMap.find(id)->second;
	return *it;
}

bool textureListBoxUI::GetIsDrop()
{
	return isDrop;
}

void textureListBoxUI::ResetIsDrop()
{
	isDrop = false;
	
	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it)
	{
		delete it->second;
	}
	spriteMap.clear();
}

string& textureListBoxUI::GetId()
{
	return id;
}
