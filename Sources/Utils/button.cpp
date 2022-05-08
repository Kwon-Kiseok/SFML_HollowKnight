#include "button.hpp"
#include "../Managers/InputManager.hpp"

#include <iostream>

button::button()
{
}

button::button(string text, Vector2f pos, Vector2f size)
{
	isClick = false;
	position = pos;
	state = Button_state::normal;

	buttonShape.setSize(size);
	buttonShape.setOrigin(buttonShape.getGlobalBounds().width / 2, buttonShape.getGlobalBounds().height / 2);
	buttonShape.setPosition(position);
	buttonShape.setFillColor(Color::White);

	font.loadFromFile("Resources/Fonts/CALIST.TTF");
	this->text.setString(text);
	this->text.setPosition(buttonShape.getPosition());
	this->text.setOrigin(buttonShape.getOrigin());
	this->text.setFillColor(Color::Black);
	this->text.setFont(font);
	this->text.setCharacterSize(20.f);
}

button::~button()
{
}

string button::GetText()
{
	return text.getString();
}

void button::update()
{
	Vector2i mousePosition = InputManager::GetInstance().GetMousePosition();

	bool mouseInButton = mousePosition.x >= buttonShape.getPosition().x - buttonShape.getGlobalBounds().width / 2
		&& mousePosition.x <= buttonShape.getPosition().x + buttonShape.getGlobalBounds().width / 2
		&& mousePosition.y >= buttonShape.getPosition().y - buttonShape.getGlobalBounds().height / 2
		&& mousePosition.y <= buttonShape.getPosition().y + buttonShape.getGlobalBounds().height / 2;

	Click(mouseInButton);

	switch (state)
	{
	case Button_state::clicked:
		buttonShape.setFillColor(Color::Red);
		break;
	case Button_state::hovered:
		buttonShape.setFillColor(Color::Green);
		break;
	case Button_state::normal:
		buttonShape.setFillColor(Color::White);
		break;
	}
}

void button::Click(bool isHovered)
{
	if (isHovered)
	{
		if (InputManager::GetInstance().GetMouseButtonDown(Mouse::Left))
		{
			state = Button_state::clicked;
			isClick = true;
		}
		else if (InputManager::GetInstance().GetMouseButtonUp(Mouse::Left) && isClick == true)
		{
			state = Button_state::hovered;
			isClick = false;
		}
		if (!isClick)
		{
			state = Button_state::hovered;
		}
	}
	else
	{
		state = Button_state::normal;
	}
}

void button::draw(RenderWindow& window)
{
	window.draw(buttonShape);
	window.draw(text);
}

bool button::IsButtonClicked()
{
	return isClick;
}

void button::ResetIsClicked()
{
	isClick = false;
}
