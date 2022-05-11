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

	float Gravity = 1800.f;
	float gravity;				//�߷°��ӵ�
	float _velocity_x = 10;		//x���� �ʱ�ӵ�
	float _velocity_y = -20;	//���� �����ø��� ���� �ʱⰪ
	bool isFalling;

public:
	Coin() {}
	Coin(Vector2f pos);
	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);

	int PickUp();
	void Spawn(bool spawned);
};

