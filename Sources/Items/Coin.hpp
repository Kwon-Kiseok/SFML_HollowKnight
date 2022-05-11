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

	float Gravity = 1800.f;
	float gravity;				//중력가속도
	float _velocity_x = 10;		//x축의 초기속도
	float _velocity_y = -20;	//위로 던져올리기 위한 초기값
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

