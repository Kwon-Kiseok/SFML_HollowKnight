#pragma once
#include "../Animation/AnimationController.hpp"
#include <map>
//#include "../DemoTile.hpp"

class Player
{
private:
	bool isWay;	// true�� ������ �ٶ󺸴� ��Ȳ
	bool isJump;
	bool isBottom;

	bool isDash;
	bool isString;

	float speed;

	Sprite sprite;
	Vector2f position;
	AnimationController animation;

	//Texture texture;
	std::map<std::string, Texture> texMap;

	Vector2f dashTemp;

	//std::string string;
	//std::string Queuestrig;
public:
	Player();
	void Init();

	void UpdateInput();
	void Update(float dt, FloatRect tile);
	void Draw(RenderWindow& window);

	const FloatRect GetGlobalBounds();	// �浹üũ �� �ʿ�
	bool UpdateCollision();	//  ���� ���� ����

	const Vector2f GetPosition();
	const Sprite GetSprite();

	bool OnHitted(Time timeHit);	// ���� ���� ����
};

