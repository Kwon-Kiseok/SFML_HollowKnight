#include "PauseUI.hpp"
#include "../Managers/ViewManager.hpp"
#include "../Managers/UIManager.hpp"
#include "../Managers/SceneManager.hpp"
#include "../Managers/InputManager.hpp"
#include "../Animation/rapidcsv.hpp"

PauseUI::PauseUI()
{
	Init();
}

PauseUI::~PauseUI()
{
}

void PauseUI::Init()
{
	float resolution_x = ViewManager::GetInstance().GetResolution().x;
	float resolution_y = ViewManager::GetInstance().GetResolution().y;

	pauseButtons[L"resume"] = new button("resume", Vector2f(resolution_x/2, resolution_y/2-100.f), Vector2f(120.f, 40.f));
	pauseButtons[L"returnToMenu"] = new button("return to menue", Vector2f(resolution_x / 2, resolution_y / 2-50.f), Vector2f(120.f, 40.f));

	pauseButtons[L"resume"]->Select(true);
	currentSelectButtonID = L"resume";

	spritePauseTop.setPosition(Vector2f(resolution_x / 2, resolution_y / 2 - 200.f));
	animContoller.SetTarget(&spritePauseTop);
	SetAnimation();
	animContoller.SetSpeed(2.f);
}

void PauseUI::Update(float dt)
{
	pauseButtons[currentSelectButtonID]->Select(true);
	for (auto& button : pauseButtons)
	{
		button.second->update(dt);

		if ((InputManager::GetInstance().GetKeyDown(Keyboard::Up) || InputManager::GetInstance().GetKeyDown(Keyboard::Down))
			&& (button.second->IsButtonSelect()))
		{
			if (currentSelectButtonID == "resume")
			{
				button.second->Select(false);
				currentSelectButtonID = L"returnToMenu";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
			else if (currentSelectButtonID == "returnToMenu")
			{
				button.second->Select(false);
				currentSelectButtonID = L"resume";
				SoundManager::GetInstance().PlaySound(L"changeMenu");
			}
		}
		else if (InputManager::GetInstance().GetKeyDown(Keyboard::Enter) && (button.second->IsButtonSelect()))
		{
			if (currentSelectButtonID == "resume")
			{
				UIManager::GetInstance().SetIsPause(false);
				pauseButtons[L"resume"]->ResetIsClicked();
			}
			else if (currentSelectButtonID == "returnToMenu")
			{
				//메뉴로 돌아가기
				SceneManager::GetInstance().Load(L"Title");
				UIManager::GetInstance().SetIsPause(false);
				pauseButtons[L"returnToMenu"]->ResetIsClicked();
			}
		}

		for (auto check : pauseButtons)
		{
			if (check.second->IsButtonSelect())
			{
				if (check.first != currentSelectButtonID)
				{
					pauseButtons[currentSelectButtonID]->Select(false);

					currentSelectButtonID = check.first;
				}
			}
		}
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

	animContoller.Update(dt);
}

void PauseUI::Render(RenderWindow& window)
{
	for (auto& button : pauseButtons)
	{
		button.second->draw(window);
		window.draw(spritePauseTop);
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

void PauseUI::SetAnimation()
{
	rapidcsv::Document clips("data_tables/animations/ui/pause_anim_clips.csv");

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

AnimationController& PauseUI::GetAnim()
{
	return animContoller;
}
