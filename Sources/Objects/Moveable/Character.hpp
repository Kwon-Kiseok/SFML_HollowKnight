#pragma once
#include "../GameObject.hpp"
#include "../../Animation/AnimationController.hpp"

enum class Direction { NONE, LEFT, RIGHT, UP, DOWN };
enum class State { IDLE, MOVE };

class Character : public GameObject
{
protected:
	int health;					// ĳ������ ü��
	int shield;					// ����
	
	Vector2f colDir;			// ĳ������ �浹 ����
	Direction currentDir;		// ĳ������ ���� ����
	float gravity;				// �߷°�
	float moveSpeed;			// �̵��ӵ�	
	float jumpSpeed;			// �����ӵ�	
	float deltaTime;			// dt
	
	bool isShield;				// ���� ���� Ȯ��
	bool isAlive;				// ���� Ȯ��
	bool isJumping;				// ���� ���� ������
	bool isFalling;				// ���� �������� ������
	bool isColliding;			// ���� �浹������
	
	AnimationController animContoller;	// �ִϸ��̼� ��Ʈ�ѷ�
	
	State state;				// ĳ���Ͱ� �̵� ������

	int xDir;// x�࿡ ���� ����
	int yDir;// y�࿡ ���� ����

	RectangleShape detectShape;	// �߰� �ڽ�
	RectangleShape attackBox;	// ���� �ڽ�
	bool isDetect;				// �߰� �Ǵ�
	float lodingTime;			// �ε� �ð�
	bool isLoading;				// �ε� ������

public:
	bool canMove;			// ������ �� �ִ� ��������
	bool canJump;			// ������ �� �ִ� ��������
	bool canFall;			// ������ �� �ִ� ��������

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
	virtual void SetShield(int shield);						// ���� ��ȯ
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
	virtual void Update(float dt, Vector2f pos);
	virtual void Render(RenderWindow& window);
	virtual void Release();
	
	virtual void OnGround(FloatRect map);					// �ʰ� �浹ó��	
	virtual bool GetIsAlivve();								// ����ִ��� �Ǵ�
	virtual bool GetIsIsShield();							// ���� �Ǵ�
	// �÷��̾� �߰�
	virtual RectangleShape GetDetectShape();				// Ž�� �ڽ�
	virtual RectangleShape GetAttackShape();				// ���� �ڽ�
	virtual RectangleShape GetRectangleShape();				// 
	virtual void SetIsDetect(bool is);

	virtual bool GetIsLoading();
	virtual void SetIsLoading(bool is);
};

