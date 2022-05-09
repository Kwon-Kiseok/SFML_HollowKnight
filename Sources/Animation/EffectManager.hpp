#pragma once
#include "AnimationController.hpp"

using namespace sf;

class EffectManager
{
private:
	Sprite effectSprite;
	Vector2f position;
	AnimationController effect;

	//Texture texture;
	std::map<std::string, Texture> texMap;
public:
	void Init();

	void Update(Vector2f playerPosition);
	void Draw(RenderWindow& window);

	void SetDraw(std::string string);
};

