#pragma once
#include "../Animation/AnimationController.hpp"
#include <map>
#include "../DemoTile.hpp"

class Player
{
private:
	bool isWay;	// true면 왼쪽을 바라보는 상황
	bool isJump;
	bool isBottom;

	int hp;
	int mp;

	bool isDash;
	bool isString;

	float speed;

	Sprite sprite;
	Vector2f position;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f dashTemp;

	std::string string;
	std::string Queuestrig;

public:
	Player();
	void Init();

	void UpdateInput();
	void Update(float dt, FloatRect tile);
	void Draw(RenderWindow& window);

	FloatRect GetGlobalBounds();

	Vector2f GetPosition();
	void SetPosition(Vector2f pos);
	int GetHP();
	int GetMP();
	void AddHP(int value);
	void AddMP(int value);
};

