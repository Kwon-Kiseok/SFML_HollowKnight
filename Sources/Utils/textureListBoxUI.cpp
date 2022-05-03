#include "textureListBoxUI.hpp"

textureListBoxUI::textureListBoxUI()
{
	ListBox.setSize(Vector2f(700.f, 500.f));
	ListBox.setOrigin(ListBox.getGlobalBounds().width / 2, ListBox.getGlobalBounds().height / 2);
	ListBox.setPosition(1920.f * 0.5f, 1080.f * 0.5f);
	ListBox.setFillColor(Color::White);

	closeButton = new button("Close", Vector2f(ListBox.getPosition().x, ListBox.getPosition().y + (ListBox.getGlobalBounds().height / 2) - 20.f), Vector2f(80.f, 25.f));
}

textureListBoxUI::~textureListBoxUI()
{
}

void textureListBoxUI::Update(bool* isOpen)
{
	// 텍스처 윈도우 창이 열려있을 때만
	if (*isOpen)
	{
		// 클로즈 버튼 활성화
		closeButton->update();
	}
	if (closeButton->IsButtonClicked())
	{
		*isOpen = false;
		closeButton->ResetIsClicked();
	}
}

void textureListBoxUI::Render(RenderWindow& window)
{
	window.draw(ListBox);
	closeButton->draw(window);
}

void textureListBoxUI::Release()
{
	delete closeButton;

	for (auto it = textureMap.begin(); it != textureMap.end(); ++it)
	{
		delete it->second;
	}
	textureMap.clear();

	for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it)
	{
		delete it->second;
	}
	spriteMap.clear();
}
