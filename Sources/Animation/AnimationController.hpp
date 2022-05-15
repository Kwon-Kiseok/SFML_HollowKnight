#pragma once
#include "AnimationClip.hpp" // �ִϸ��̼� Ŭ���� ����־���Ѵ�
#include <map>	// vector�� �ص� ������ �̸��� ã���� ���ϰ� �ϱ�����
#include <queue>

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips;	// �� Ŭ���� ���� �����ϳ�??? ���ھֵ���????
	std::queue<std::string> playQueue;

	AnimationClip* currentClip;
	bool isPlaying;	// ���� ������ΰ��� Ȯ��
	int currentFrame;	//
	int totalFrame;	// ����ϴ� �ִϸ��̼��� �� ����
	float frameDurtion;

	float accumTime;

	Sprite* sprite;	// �갡 �����ϴ°� �ƴ϶� �÷��̾��� ������� �޾ƿͼ� ���...

	float speed;
public:
	AnimationController();

	void SetTarget(Sprite* sprite);
	void AddClip(const AnimationClip& newClip);

	void Update(float dt);	// ��ŸŸ���� �޾ƿ��� ������Ʈ

	void Play(std::string clipId, bool clear = true);	// �÷���
	void PlayQueue(std::string clipId);

	void Stop();	// ����
	// �ۿ��� ����� Get�Լ���
	bool IsPlaying();
	bool IsPlaying(std::string clipId);

	void SetSpeed(float speed);

	void ClearPlayQueue();
};

