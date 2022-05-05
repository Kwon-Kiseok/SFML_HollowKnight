#pragma once
#include "../GameObject.hpp"
#include "../../Animation/AnimationController.hpp"
#include <string>

enum class Direction { NONE, LEFT, RIGHT, UP, DOWN };

class Character : public GameObject
{
protected:
	std::string name;			// ĳ������ �̸� �ο�
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
	
public:
	bool canMove;			// ������ �� �ִ� ��������
	bool canJump;			// ������ �� �ִ� ��������
	bool canFall;			// ������ �� �ִ� ��������

public:
	Character();
	virtual ~Character();

	// Get Function
	std::string GetName();
	int GetHealth();
	Direction GetPrevDirection();


	// SetFunction
	void SetX(float x);
	void SetY(float y);
	void SetName(std::string name);
	void SetHealth(int health);
	void SetDirection(Direction dir);
	void SetCollisionState(bool isCol);

	void Move(Vector2f newPosition);

	virtual bool Collision(GameObject* otherObj);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(RenderWindow& window);
	virtual void Release();
};

