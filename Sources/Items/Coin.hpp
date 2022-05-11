#pragma once
#include "Item.hpp"
#include <SFML/Graphics.hpp>
#include "../Managers/SoundManager.hpp"
#include "../Utils/Utility.hpp"

class Coin : public Item
{
// 그려주는거랑 중력받는거
private:
	bool pickCoin;
	bool spawned;
	int value;

	float GRAVITY = 1800.f;
	float fallingSpeed;
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
	void OnGround();
	void Render(RenderWindow& window);

	int PickUp();
	void Spawn(bool spawn);
};

