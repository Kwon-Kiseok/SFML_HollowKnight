#pragma once
#include "../GameObject.hpp"
#include "../../Animation/AnimationController.hpp"

enum class Direction { NONE, LEFT, RIGHT, UP, DOWN };
enum class State { IDLE, MOVE };

class Character : public GameObject
{
protected:
	int health;					// 캐릭터의 체력
	int shield;					// 쉴드
	
	Vector2f colDir;			// 캐릭터의 충돌 방향
	Direction currentDir;		// 캐릭터의 현재 방향
	float gravity;				// 중력값
	float moveSpeed;			// 이동속도	
	float jumpSpeed;			// 점프속도	
	float deltaTime;			// dt
	
	bool isShield;				// 쉴드 상태 확인
	bool isAlive;				// 생존 확인
	bool isJumping;				// 현재 점프 중인지
	bool isFalling;				// 현재 떨어지는 중인지
	bool isColliding;			// 현재 충돌중인지
	
	AnimationController animContoller;	// 애니메이션 컨트롤러
	
	State state;				// 캐릭터가 이동 중인지

	int xDir;// x축에 대한 방향
	int yDir;// y축에 대한 방향

	RectangleShape detectShape;	// 추격 박스
	RectangleShape attackBox;	// 공격 박스
	bool isDetect;				// 추격 판단
	float lodingTime;			// 로딩 시간
	bool isLoading;				// 로딩 중인지

public:
	bool canMove;			// 움직일 수 있는 상태인지
	bool canJump;			// 점프할 수 있는 상태인지
	bool canFall;			// 떨어질 수 있는 상태인지

public:
	Character();
	virtual ~Character();

	// Get Function
	int GetHealth();
	Vector2f& SetColDirection(GameObject* otherObj);
	Vector2f& GetColDirection();
	Direction GetDirection();

	// SetFunction
	void SetX(float x);
	void SetY(float y);
	virtual void SetHealth(int health);
	virtual void SetShield(int shield);						// 쉴드 반환
	void SetDirection(Direction dir);
	void SetCollisionState(bool isCol);

	void Move(Vector2f newPosition);

	virtual bool Collision(GameObject* otherObj);
	/// <summary>
	/// 상대의 attackBox에 피격당했을 때
	/// </summary>
	virtual bool Collision_AttackBox(RectangleShape& attackBox);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Update(float dt, Vector2f pos);
	virtual void Render(RenderWindow& window);
	virtual void Release();
	
	virtual void OnGround(FloatRect map);					// 맵과 충돌처리	
	virtual bool GetIsAlivve();								// 살아있는지 판단
	virtual bool GetIsIsShield();							// 쉴드 판단
	// 플레이어 추격
	virtual RectangleShape GetDetectShape();				// 탐지 박스
	virtual RectangleShape GetAttackShape();				// 공격 박스
	virtual RectangleShape GetRectangleShape();				// 
	virtual void SetIsDetect(bool is);

	virtual bool GetIsLoading();
	virtual void SetIsLoading(bool is);
};

