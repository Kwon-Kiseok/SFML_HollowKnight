#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"
#include "../../Sources/Managers/InputManager.hpp"

class Vengefly : public Monster
{
private:
	AnimationController animation;

	Vector2f positionTemp;
	//Texture texture;
	std::map<std::string, Texture> texMap;

	const float GRAVITY = 1500.f;				// 중력
public:
	Vengefly();
	Vengefly(int xdir);
	virtual ~Vengefly() {}

	virtual void Init() override;
	virtual void Update(float dt, Vector2f playerPos) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGround(FloatRect map) override;

	//const FloatRect GetGlobalBounds();	// 충돌체크 때 필요
	bool UpdateCollision();	//  내가 때린 판정
	bool OnHitted(Time timeHit);	// 내가 맞은 판정

	virtual RectangleShape GetDetectShape() override;
	virtual void SetIsDetect(bool is) override;
};

