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
		// ���Ⱑ ������ �� �Դϴ�!!!
	}
}

void AnimationController::Update(float dt)
{
	if (!isPlaying)	// isPlaying �� �޽��� ������Ʈ ����
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
	if (currentFrame >= totalFrame)	// �̶� ??!?!���ϴ°���
	{
		if (playQueue.empty())
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;	// ó������ ���ư���
				//��ȯ�ǰ� �Ϸ��� currentFrame�� --�Ǵ� ������ �־���Ѵ�(���� �߰�)
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
	sprite->setTextureRect(currentClip->frames[currentFrame].texCoord);	//	��� ������ ��������

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
	frameDurtion = 1.f / currentClip->fps;	// 1�� ������ �������Ӵ� ����ϴ� �ð�?!?!
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
