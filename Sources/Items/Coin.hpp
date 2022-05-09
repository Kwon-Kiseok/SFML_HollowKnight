#pragma once
#include "Item.hpp"
#include <SFML/Graphics.hpp>

class Coin : public Item
{
private:
	int coin = 123;
public:
	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	int GetCoin();
	void SetCoin(int coin);
};

