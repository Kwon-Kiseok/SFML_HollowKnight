#pragma once
#include "Item.hpp"
#include <SFML/Graphics.hpp>

class Coin : public Item
{
// 그려주는거랑 중력받는거

public:
	Coin() {}
	Coin(Vector2f pos);
	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	
};

