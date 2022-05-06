#pragma once
#include "../Animation/AnimationController.hpp"
#include "../Objects/Moveable/Character.hpp"
#include <map>

class Player : public Character
{
private:
	const float ATTACK_DELAY = 0.3f;

	bool isWay;	// true면 왼쪽을 바라보는 상황
	bool isJump;
	bool isBottom;

	int hp;
	int mp;

	bool isDash;

	float speed;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f dashTemp;
	// 공격 범위 박스
	RectangleShape attackBox;
	Vector2f attackBoxPosition;
	bool isAttack;
	float attackDelay;
	// 플레이어 히트박스
	RectangleShape hitBox;
	Vector2f hitBoxPosition;
public:
	Player();
	virtual void Init() override;

	void UpdateInput();
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
	int GetHP();
	int GetMP();
	void AddHP(int value);
	void AddMP(int value);
	const FloatRect GetGlobalBounds();	// 충돌체크 때 필요
	bool UpdateCollision();	//  내가 때린 판정
	bool OnHitted(Time timeHit);	// 내가 맞은 판정
};

