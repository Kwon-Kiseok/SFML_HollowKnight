#pragma once
#include "Item.hpp"
#include <SFML/Graphics.hpp>
#include "../Managers/SoundManager.hpp"
#include "../Utils/Utility.hpp"

class Coin : public Item
{
// �׷��ִ°Ŷ� �߷¹޴°�
private:
	bool pickCoin;
	bool spawned;
	int value;

	float GRAVITY = 1800.f;
	float fallingSpeed;
	float _velocity_x = 10;		//x���� �ʱ�ӵ�
	float _velocity_y = -20;	//���� �����ø��� ���� �ʱⰪ
	
	bool isFalling;
	bool isCollideCoin;
	Vector2f PositionCoin;
public:
	Coin() {}
	Coin(Vector2f pos);
	void Init();
	void Update(float dt);
	void OnGround();
	void Render(RenderWindow& window);

	int PickUp();
	void Spawn(bool spawn);
};

