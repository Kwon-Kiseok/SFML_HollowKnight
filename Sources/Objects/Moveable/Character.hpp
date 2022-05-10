#pragma once
#include "../GameObject.hpp"
#include "../../Animation/AnimationController.hpp"

enum class Direction { NONE, LEFT, RIGHT, UP, DOWN };
enum class State { IDLE, MOVE };

class Character : public GameObject
{
protected:
	int health;					// ĳ������ ü��
	Direction prevDir;			// ĳ������ ���� ����
	Direction currentDir;		// ĳ������ ���� ����
	float gravity;				// �߷°�
	float moveSpeed;			// �̵��ӵ�	
	float jumpSpeed;			// �����ӵ�	
	float deltaTime;			// dt
	
	bool isJumping;				// ���� ���� ������
	bool isFalling;				// ���� �������� ������
	bool isColliding;			// ���� �浹������
	
	AnimationController animContoller;	// �ִϸ��̼� ��Ʈ�ѷ�
	
	State state;				// ĳ���Ͱ� �̵� ������

	int xDir;// x�࿡ ���� ����
	int yDir;// y�࿡ ���� ����
public:
	bool canMove;			// ������ �� �ִ� ��������
	bool canJump;			// ������ �� �ִ� ��������
	bool canFall;			// ������ �� �ִ� ��������

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
	/// ����� attackBox�� �ǰݴ����� ��
	/// </summary>
	virtual bool Collision_AttackBox(RectangleShape& attackBox);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(RenderWindow& window);
	virtual void Release();

	virtual void OnGround(FloatRect map);
};

