#pragma once
#include "../Animation/AnimationController.hpp"
#include "../Objects/Moveable/Character.hpp"
#include <map>

class Player : public Character
{
private:
	bool isWay;	// true면 왼쪽을 바라보는 상황
	bool isJump;
	bool isBottom;

	int hp;
	int mp;

	bool isDash;
	bool isString;

	float speed;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f dashTemp;
  
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

