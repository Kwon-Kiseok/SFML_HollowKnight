#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"
#include "../../Sources/Managers/InputManager.hpp"

class FalseKnight : public Monster
{
private:
	RectangleShape attackBox;

	float downTime;

	const float GRAVITY = 1500.f;	// 중력
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
	virtual RectangleShape GetDetectShape() override;		// 공격 범위
	virtual void SetIsDetect(bool is) override;
};

