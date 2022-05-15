#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"
#include "../../Sources/Managers/InputManager.hpp"

class FalseKnight : public Monster
{
private:
	const int SHIELD = 4;			// 최대 쉴드
	const float DOWNTIME = 4.f;		// 스턴상태의 시간
	const float GRAVITY = 1500.f;	// 중력
	const float ATTACK_DELAY = 4.f;	// 공격 딜레이 시간

	AnimationController animation;
	std::map<std::string, Texture> texMap;

	Vector2f attackBoxPos;			// 공격 박스 포지션
	bool isAttack = false;			// 공격 여부
	int attackPattern;				// 공격 패턴
	int attackDir;					// 공격 방향
	Texture texture;
	Sprite waveSprite;

	float downTime;					// 스턴상태 시간 계산
	float attackDelay;				// 공격의 딜레이 시간 계산

	bool isOne = false;				// 스턴 이미지 한번만
public:
	FalseKnight();
	FalseKnight(int xdir);
	virtual ~FalseKnight() {}

	virtual void Init() override;
	virtual void Update(float dt, Vector2f player) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGround(FloatRect map) override;

	bool OnHitted(Time timeHit);	// 내가 맞은 판정

	virtual void SetShield(int shield);						// 쉴드 반환
	virtual RectangleShape GetDetectShape() override;		// 탐지 범위
	virtual void SetIsDetect(bool is) override;				// 공격 여부
	virtual void SetHealth(int health) override;

	void Attack(float dt);
};