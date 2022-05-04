#pragma once
#include "../Animation/AnimationController.hpp"
#include <map>
#include "../DemoTile.hpp"

class Player
{
private:
	bool isMove;
	bool isWay;
	bool isJump;
	bool isBottom;

	float speed;

	Sprite sprite;
	Vector2f position;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;
public:
	Player();
	void Init();

	void UpdateInput();
	void Update(float dt, FloatRect tile);
	void Draw(RenderWindow& window);

	FloatRect GetGlobalBounds();
};

