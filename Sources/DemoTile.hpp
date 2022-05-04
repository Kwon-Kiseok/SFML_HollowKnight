#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class DemoTile
{
private:
	Vector2f position;
	RectangleShape shape; // 그리기용 함수

public:
	DemoTile();
	DemoTile(float x, float y);

	FloatRect GetGlobalBounds();	// 충돌 체크
	const RectangleShape& GetShape();

	void Update(float dt);
};

