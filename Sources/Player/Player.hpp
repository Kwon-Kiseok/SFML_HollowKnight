#pragma once
#include "../Animation/AnimationController.hpp"
#include <map>
#include "../Objects/GameObject.hpp"
#include "../DemoTile.hpp"


class Player : public GameObject
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
	void Init();

	void UpdateInput();
	void Update(float dt, FloatRect tile);
	void Draw(RenderWindow& window);

	int GetHP();
	int GetMP();
	void AddHP(int value);
	void AddMP(int value);
	const FloatRect GetGlobalBounds();	// 충돌체크 때 필요
	bool UpdateCollision();	//  내가 때린 판정
	bool OnHitted(Time timeHit);	// 내가 맞은 판정
};

