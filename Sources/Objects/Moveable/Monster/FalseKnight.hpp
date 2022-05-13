#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"
#include "../../Sources/Managers/InputManager.hpp"

class FalseKnight : public Monster
{
private:
	RectangleShape attackBox;

	float downTime;

	const float GRAVITY = 1500.f;	// �߷�
public:
	FalseKnight();
	FalseKnight(int xdir);
	virtual ~FalseKnight() {}

	virtual void Init() override;
	virtual void Update(float dt, Vector2f player) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGround(FloatRect map) override;

	bool OnHitted(Time timeHit);	// ���� ���� ����

	virtual void SetShield(int shield);						// ���� ��ȯ
	virtual RectangleShape GetDetectShape() override;		// ���� ����
	virtual void SetIsDetect(bool is) override;
};

