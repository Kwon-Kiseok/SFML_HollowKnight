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
	float _velocity_x = 10;		//x축의 초기속도
	float _velocity_y = -20;	//위로 던져올리기 위한 초기값
	
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

