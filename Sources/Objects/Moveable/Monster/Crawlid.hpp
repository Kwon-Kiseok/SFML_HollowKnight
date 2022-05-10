#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"

class Crawlid : public Monster
{
private:
	AnimationController animation;

	RectangleShape gavityShape;

	Vector2f positionTemp;
	//Texture texture;
	std::map<std::string, Texture> texMap;

	const float GRAVITY = 1500.f;				// 중력
	float gravity;								// 중력가속도 처리
public:
	Crawlid();
	Crawlid(int xdir);
	virtual ~Crawlid() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGround(FloatRect map) override;
};

