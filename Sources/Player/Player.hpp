#pragma once
#include "../Animation/AnimationController.hpp"
#include "../Animation/SlashEffect.hpp"
#include "../Animation/DashEffect.hpp"
#include "../Objects/Moveable/Character.hpp"
#include "../Managers/MapManager.hpp"
#include <map>
#include "../Items/Coin.hpp"

class Player : public Character
{
private:
	const float ATTACK_DELAY = 0.5f;			// 공격 딜레이
	const float GRAVITY = 1500.f;				// 중력
	const float SPEED = 300.f;					// 이동속도
	const float JUMP_MAX = 1.f;					// 최대 점프

	bool isWay;									// true면 왼쪽을 바라보는 상황 (필요함)
	bool isDash;								// 필요함
	bool canDash = false;						// 공중에서 대쉬 한번만 할 수 있게
	float dashDelay = 1.f;

	//int hp;										// 체력
	int mp;										// 기력?
	int coin;									// 재화
	MAP_TYPE currMap;							// 현재 맵

	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f dashTemp;							// 대쉬 시작 포지션
	// 공격 범위 박스
	RectangleShape attackBox;
	bool isAttack;								// 공격 판정 온오프
	bool hitAttack;								// 
	float attackDelay;							// 공격 딜레이
	int AttackDir;								// 공격 방향 0 = 좌우, 1 = 하단, -1 = 상단
	int collisionType;							// collisitionType 0 = 몬스터, 1 = 맵, 2 = 트랩
	// 플레이어 히트박스
	RectangleShape hitBox;
	// 좌우 벽 충돌처리
	//RectangleShape hitBoxSide;

	float gravity;								// 중력가속도 처리
	Vector2f positionTemp;						// 전 프레임 포지션
	float jumpTime;								// 점프 누를 수 있는 시간

	float move;									// 전 프레임의 좌우 이동 방향 값 저장

	std::string string;							// 이미지 저장

	bool isKnockback = false;
	float knockbackTime;
	float knockbackX;							// 피격 당했을시 날아갈 힘

	SlashEffect effect;							// Slash이펙트
	std::string effectString;					// 공격 이펙트 방향 저장
	std::string attackString;					// 공격 애니메이션 방향 저장
	DashEffect dashDffect;						// 대쉬 이펙트

	float collisionTime;						// 맞는 딜레이

public:
	Player();
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	int GetHP();
	int GetMP();
	int GetCoin();
	void AddHP(int value);
	void AddMP(int value);
	void AddCoin(int value);
	const FloatRect GetGlobalBounds();	// 충돌체크 때 필요
	void UpdateCollision(int type);	//  내가 때린 판정
	void OnHitted(Vector2f pos);	// 내가 맞은 판정

	void OnGround(FloatRect map);
	void SetXpos();
	//void SetVal(float dt);

	const RectangleShape GetAttackBox();
	const RectangleShape GetHitBox();
	/** test **/
	//Vector2f GetPosition();
	void SetHP();
	bool GetIsAttackBox();
	void SetIsAttackBox(bool is);

	MAP_TYPE GetCurrentMap();
	void SetCurrentMap(MAP_TYPE type);
	bool UpdateCollision(const std::list<Coin*> coins);
};

