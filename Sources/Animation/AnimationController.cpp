#include "AnimationController.hpp"

#include <iostream>

AnimationController::AnimationController()
	: clips(), currentClip(nullptr), isPlaying(false), currentFrame(-1), totalFrame(0), frameDurtion(0.f), accumTime(0.f), sprite(nullptr), speed(1.f)
{
}

void AnimationController::SetTarget(Sprite* sprite)
{
	this->sprite = sprite;
}

void AnimationController::AddClip(const AnimationClip& newClip)
{
	if (clips.find(newClip.id) == clips.end())
	{
		clips[newClip.id] = newClip;
	}
	else
	{
		// 여기가 오류일 때 입니당!!!
	}
}

void AnimationController::Update(float dt)
{
	if (!isPlaying)	// isPlaying 이 펄스면 업데이트 안함
	{
		return;
	}

	accumTime += dt * speed;
	if (accumTime < frameDurtion)
	{
		return;
	}

	accumTime = 0.f;
	++currentFrame;
	if (currentFrame >= totalFrame)	// 이때 ??!?!뭐하는거지
	{
		if (playQueue.empty())
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;	// 처음으로 돌아가기
				//순환되게 하려면 currentFrame이 --되는 구간이 있어아한다(변수 추가)
				break;
			default:
				// Error
				break;
			}
		}
		else
		{
			std::string nextClipId = playQueue.front();
			playQueue.pop();
			Play(nextClipId, false);
		}		
		
	}

	sprite->setTexture(currentClip->frames[currentFrame].texture);
	sprite->setTextureRect(currentClip->frames[currentFrame].texCoord);	//	어느 영역을 찍을건지

	sprite->setOrigin(currentClip->frames[currentFrame].origin);
}

void AnimationController::Play(std::string clipId, bool clear)
{
	if (clear)
	{
		ClearPlayQueue();
	}

	isPlaying = true;
	currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->frames.size();
	frameDurtion = 1.f / currentClip->fps;	// 1로 나눠서 한프레임당 재생하는 시간?!?!
}

void AnimationController::PlayQueue(std::string clipId)
{
	isPlaying = true;
	playQueue.push(clipId);
}

void AnimationController::Stop()
{
	isPlaying = false;
	ClearPlayQueue();
}

bool AnimationController::IsPlaying()
{
	return isPlaying;
}

bool AnimationController::IsPlaying(std::string clipId)
{
	if (currentClip->id == clipId)
	{
		return isPlaying;
	}
	return false;
}

void AnimationController::SetSpeed(float speed)
{
	this->speed = speed;
}

void AnimationController::ClearPlayQueue()
{
	while (!playQueue.empty())
	{
		playQueue.pop();
	}
}
