#pragma once
#include "Item.hpp"
#include <SFML/Graphics.hpp>
#include "../Managers/SoundManager.hpp"
#include "../Utils/Utility.hpp"

class Coin : public Item
{
private:
	bool pickCoin;
	int value;

	const float GRAVITY = 1800.f;
	float fallingSpeed = 10;
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
	void Render(RenderWindow& window);
	void OnGround();

	int PickUp();
	void SetPosition(Vector2f crawlidPosition);

	FloatRect GetGlobalBounds();
	virtual bool Collision(GameObject* otherObj) override;
};

