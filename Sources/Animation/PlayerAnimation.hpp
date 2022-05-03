#pragma once
#include "AnimationController.hpp"
#include <map>

using namespace sf;

class PlayerAnimation
{
private:
	bool isMove = true;
	bool isWay = true;
	bool isJump = true;

	Sprite sprite;
	Vector2f position;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;
public:
	void Init();

	void UpdateInput();
	void Update(float dt);
	void Draw(RenderWindow& window);
};

