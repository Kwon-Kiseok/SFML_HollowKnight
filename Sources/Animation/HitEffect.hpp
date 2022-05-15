#pragma once
#include "AnimationController.hpp"

using namespace sf;

class HitEffect
{
private:
	Sprite effectSprite;
	Vector2f position;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;
public:
	void Init();

	void Update(Vector2f playerPosition, float dt);
	void Draw(RenderWindow& window);

	void SetDraw(std::string string);
	void SwapScale();
	void SetOrigin(float x, float y);
};

