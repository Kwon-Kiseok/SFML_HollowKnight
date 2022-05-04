#pragma once
#include "Map.hpp"

using namespace sf;

class CrossRoad_Map : public Map
{
private:
	Texture textureBG;
	Sprite spriteBG;

	// 입장할 때 플레이어 포지션이 있어야함
	// 연결된 포탈 경로마다 맵이 전환될 때 같이 넘겨주던가
	Vector2f startPos;

public:
	CrossRoad_Map() {}
	~CrossRoad_Map() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(sf::RenderWindow& window) override;
	virtual void Release() override;
};

