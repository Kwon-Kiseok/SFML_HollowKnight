#pragma once
#include "../Animation/AnimationController.hpp"
#include "../Animation/EffectManager.hpp"
#include "../Objects/Moveable/Character.hpp"
#include <map>

class Player : public Character
{
private:
	const float ATTACK_DELAY = 0.5f;			// 공격 딜레이
	const float GRAVITY = 1500.f;				// 중력
	const float SPEED = 300.f;					// 이동속도
	const float JUMP_MAX = 1.f;					// 최대 점프

	bool isWay;									// true면 왼쪽을 바라보는 상황 (필요함)
	bool isDash;								// 필요함
	bool firstFrame;
	bool secondFrame;

	int hp;										// 체력
	int mp;										// 기력?

	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f dashTemp;							// 대쉬 시작 포지션
	// 공격 범위 박스
	RectangleShape attackBox;
	bool isAttack;								// 공격 판정 온오프
	float attackDelay;							// 공격 딜레이
	// 플레이어 히트박스
	RectangleShape hitBox;
	// 좌우 벽 충돌처리
	RectangleShape hitBoxSide;
	int isMove = 1;

	float gravity;								// 중력가속도 처리
	Vector2f positionTemp;						// 전 프레임 포지션
	float jumpTime;								// 점프 누를 수 있는 시간 ?? 어뜨케 쓰징

	float move;									// 전 프레임의 좌우 이동 방향 값 저장

	std::string string;							// 이미지 저장

	bool isKnockback = false;
	float knockbackTime = 0.3f;

	EffectManager effect;						// 이펙트
	std::string effectString;					// 공격 이펙트 방향 저장
	std::string attackString;					// 공격 애니메이션 방향 저장

	int knock = 0;
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

	void OnGround(FloatRect map);
	void SetXpos();
	//void SetVal(float dt);

	const RectangleShape GetAttackBox();
	/** test **/
	//Vector2f GetPosition();
	void KnockBackSide();
	void KnockBackUp();

};

