#pragma once
#include "Item.hpp"
#include <SFML/Graphics.hpp>

class Coin : public Item
{
// �׷��ִ°Ŷ� �߷¹޴°�

public:
	Coin() {}
	Coin(Vector2f pos);
	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	
};

