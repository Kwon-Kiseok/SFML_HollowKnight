#pragma once
#include "AnimationClip.hpp" // 애니메이션 클립은 들고있어야한다
#include <map>	// vector로 해도 되지만 이름을 찾을때 편하게 하기위해
#include <queue>

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips;	// 이 클립은 누가 세팅하냐??? 각자애들이????
	std::queue<std::string> playQueue;

	AnimationClip* currentClip;
	bool isPlaying;	// 현재 재생중인것을 확인
	int currentFrame;	//
	int totalFrame;	// 재생하는 애니매이션의 총 개수
	float frameDurtion;

	float accumTime;

	Sprite* sprite;	// 얘가 생성하는게 아니라 플레이어의 멤버에서 받아와서 사용...

	float speed;
public:
	AnimationController();

	void SetTarget(Sprite* sprite);
	void AddClip(const AnimationClip& newClip);

	void Update(float dt);	// 델타타임을 받아오는 업데이트

	void Play(std::string clipId, bool clear = true);	// 플레이
	void PlayQueue(std::string clipId);

	void Stop();	// 정지
	// 밖에서 사용할 Get함수들
	bool IsPlaying();
	bool IsPlaying(std::string clipId);

	void SetSpeed(float speed);

	void ClearPlayQueue();
};

