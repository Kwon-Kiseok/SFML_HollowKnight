#pragma once
#include "Map.hpp"

using namespace sf;

class Player;
class DemoTile;
class KingsPass_Map : public Map
{
private:
	Texture textureBG;
	Sprite spriteBG;

	// ������ �� �÷��̾� �������� �־����
	// ����� ��Ż ��θ��� ���� ��ȯ�� �� ���� �Ѱ��ִ���
	Vector2f startPos;

	Player* player;
	DemoTile* tile;
public:
	KingsPass_Map() {}
	~KingsPass_Map() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

