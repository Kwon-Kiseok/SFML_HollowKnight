#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class DemoTile
{
private:
	Vector2f position;
	RectangleShape shape; // �׸���� �Լ�

public:
	DemoTile();
	DemoTile(float x, float y);

	FloatRect GetGlobalBounds();	// �浹 üũ
	const RectangleShape& GetShape();

	void Update(float dt);
};

