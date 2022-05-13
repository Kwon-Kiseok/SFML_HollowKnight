#include "PauseUI.hpp"
#include "../Managers/UIManager.hpp"
#include "../Managers/SceneManager.hpp"

PauseUI::PauseUI()
{
	Init();
}

PauseUI::~PauseUI()
{
}

void PauseUI::Init()
{
	pauseButtons[L"resume"] = new button("resume", Vector2f(850.f, 450.f), Vector2f(120.f, 40.f));
	pauseButtons[L"returnToMenu"] = new button("return to menue", Vector2f(850.f, 500.f), Vector2f(120.f, 40.f));
}

void PauseUI::Update(float dt)
{
	for (auto& button : pauseButtons)
	{
		button.second->update();
	}

	if (pauseButtons[L"resume"]->IsButtonClicked())
	{
		UIManager::GetInstance().SetIsPause(false);
		pauseButtons[L"resume"]->ResetIsClicked();
	}

	if (pauseButtons[L"returnToMenu"]->IsButtonClicked())
	{
		//메뉴로 돌아가기
		SceneManager::GetInstance().Load(L"Title");
		UIManager::GetInstance().SetIsPause(false);
		pauseButtons[L"returnToMenu"]->ResetIsClicked();
	}

}

void PauseUI::Render(RenderWindow& window)
{
	for (auto& button : pauseButtons)
	{
		button.second->draw(window);
	}
}

void PauseUI::Release()
{
	for (auto& button : pauseButtons)
	{
		delete button.second;
		button.second = nullptr;
	}
	pauseButtons.clear();
}
