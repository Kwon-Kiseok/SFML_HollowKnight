#include "PlayerAnimation.hpp"
#include "rapidcsv.hpp"
#include "../Managers/InputManager.hpp"

void PlayerAnimation::Init()
{
	position.x = 1920.f / 2;
	position.y = 1080.f / 2;
	sprite.setPosition(position);

	sprite.setOrigin(31, 0);
	// Animator 초기화
	animation.SetTarget(&sprite);

	/**************************************************************************/

	rapidcsv::Document clips("data_tables/animations/player/player_animation_clips.csv");

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

		float orgX = colW[0] * 0.5f;
		float orgY = colH[0] * 0.5f;

		int totalFrames = colTexure.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexure[i]) == texMap.end())
			{
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j])));
		}
		//sprite.setOrigin(orgX, orgY);
		// Animator 초기화		// AnimationController Update에서 오리진 값 변경
		//animation.SetTarget(&sprite);

		animation.AddClip(clip);
	}

	animation.Play("Idle");
}

void PlayerAnimation::UpdateInput()
{
	// 좌우 입력시 이미지 방향 변화
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right))
	{
		if (isWay)
		{
			sprite.scale(-1, 1);
			isWay = !isWay;
		}
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Left))
	{
		if (!isWay)
		{
			sprite.scale(-1, 1);
			isWay = !isWay;
		}
	}
	// 좌우 이동 이미지
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyDown(Keyboard::Left))
	{
		animation.Play("StartMove");
		animation.PlayQueue("Move");
	}
	// 좌우 이동 -> 멈춤 이미지
	if ((InputManager::GetInstance().GetKeyUp(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyUp(Keyboard::Left)))
	{
		animation.Play("RunToIdle");
		animation.PlayQueue("Idle");
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Z))
	{
		animation.Play("Jump");
		animation.PlayQueue("Idle");	// 이전 이미지로
	}
	// 공격 애니메이션 or 이전 이미지 저장하는 법????
	if (InputManager::GetInstance().GetKeyDown(Keyboard::X))
	{
		animation.Play("Slash");
		animation.PlayQueue("Idle");	// 이전 이미지로
	}
}

void PlayerAnimation::Update(float dt)
{
	UpdateInput();
	animation.Update(dt);
}

void PlayerAnimation::Draw(RenderWindow& window)
{
	window.draw(sprite);
}