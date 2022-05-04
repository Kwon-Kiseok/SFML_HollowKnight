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
	// 입장할 때 플레이어 포지션이 있어야함
	// 연결된 포탈 경로마다 맵이 전환될 때 같이 넘겨주던가
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

