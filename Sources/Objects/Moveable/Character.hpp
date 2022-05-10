#pragma once
#include "../GameObject.hpp"
#include "../../Animation/AnimationController.hpp"

enum class Direction { NONE, LEFT, RIGHT, UP, DOWN };
enum class State { IDLE, MOVE };

class Character : public GameObject
{
protected:
	int health;					// 캐릭터의 체력
	Direction prevDir;			// 캐릭터의 이전 방향
	Direction currentDir;		// 캐릭터의 현재 방향
	float gravity;				// 중력값
	float moveSpeed;			// 이동속도	
	float jumpSpeed;			// 점프속도	
	float deltaTime;			// dt
	
	bool isJumping;				// 현재 점프 중인지
	bool isFalling;				// 현재 떨어지는 중인지
	bool isColliding;			// 현재 충돌중인지
	
	AnimationController animContoller;	// 애니메이션 컨트롤러
	
	State state;				// 캐릭터가 이동 중인지

	int xDir;// x축에 대한 방향
	int yDir;// y축에 대한 방향
public:
	bool canMove;			// 움직일 수 있는 상태인지
	bool canJump;			// 점프할 수 있는 상태인지
	bool canFall;			// 떨어질 수 있는 상태인지

public:
	Character();
	virtual ~Character();

	// Get Function
	int GetHealth();
	Direction GetPrevDirection();


	// SetFunction
	void SetX(float x);
	void SetY(float y);
	void SetHealth(int health);
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
	virtual void Render(RenderWindow& window);
	virtual void Release();

	virtual void OnGround(FloatRect map);
};

