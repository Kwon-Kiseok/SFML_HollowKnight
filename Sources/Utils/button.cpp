#include "button.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Animation/rapidcsv.hpp"
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
	this->text.setCharacterSize(30.f);
	this->text.setStyle(Text::Bold);
	this->text.setFillColor(Color::White);
	this->text.setFont(font);
	this->text.setPosition((pos.x - this->text.getLocalBounds().width / 2), (pos.y - this->text.getLocalBounds().height));

	spriteButton.setPosition(pos);
	animContoller.SetTarget(&spriteButton);
	SetAnimation();
	animContoller.SetSpeed(3.f);
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

void button::update(float dt)
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
		break;
	case Button_state::hovered:
		if (!animContoller.IsPlaying())
		{
			animContoller.PlayQueue("Btn_flash");
			SoundManager::GetInstance().PlaySound(L"changeMenu");
		}
		break;
	case Button_state::normal:
		animContoller.Stop();
		animContoller.ClearPlayQueue();
		break;
	}

	animContoller.Update(dt);
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
	//window.draw(buttonShape);
	if(animContoller.IsPlaying())
		window.draw(spriteButton);
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

void button::SetAnimation()
{
	rapidcsv::Document clips("data_tables/animations/ui/button_anim_clips.csv");

	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		std::vector<int> colX = frames.GetColumn<int>("X");
		std::vector<int> colY = frames.GetColumn<int>("Y");

		int totalFrames = colTexure.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexure[j]) == texMap.end())
			{
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j]), Vector2f(colX[j], colY[j])));
		}

		animContoller.AddClip(clip);
	}
}