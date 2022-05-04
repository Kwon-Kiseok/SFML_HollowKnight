#pragma once
#include "Map.hpp"
#include "../Monster/tempMob.hpp"

using namespace sf;

class Player;
class DemoTile;
class Town_Map : public Map
{
private:
	Texture textureBG;
	Sprite spriteBG;

	Texture texturePortal;
	Sprite spritePortal;
	// ������ �� �÷��̾� �������� �־����
	// ����� ��Ż ��θ��� ���� ��ȯ�� �� ���� �Ѱ��ִ���
	Vector2f startPos;

	Player* player;
	DemoTile* tile;
	tempMob* mob;

public:
	Town_Map();
	~Town_Map() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
};

