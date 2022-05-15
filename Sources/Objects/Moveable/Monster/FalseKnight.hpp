#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"
#include "../../Sources/Managers/InputManager.hpp"

class FalseKnight : public Monster
{
private:
	const int SHIELD = 4;			// �ִ� ����
	const float DOWNTIME = 4.f;		// ���ϻ����� �ð�
	const float GRAVITY = 1500.f;	// �߷�
	const float ATTACK_DELAY = 4.f;	// ���� ������ �ð�

	AnimationController animation;
	std::map<std::string, Texture> texMap;

	Vector2f attackBoxPos;			// ���� �ڽ� ������
	bool isAttack = false;			// ���� ����
	int attackPattern;				// ���� ����
	int attackDir;					// ���� ����
	Texture texture;
	Sprite waveSprite;

	float downTime;					// ���ϻ��� �ð� ���
	float attackDelay;				// ������ ������ �ð� ���

	bool isOne = false;				// ���� �̹��� �ѹ���
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
	virtual RectangleShape GetDetectShape() override;		// Ž�� ����
	virtual void SetIsDetect(bool is) override;				// ���� ����
	virtual void SetHealth(int health) override;

	void Attack(float dt);
};