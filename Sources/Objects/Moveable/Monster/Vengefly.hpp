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

	const float GRAVITY = 1500.f;				// �߷�
public:
	Vengefly();
	Vengefly(int xdir);
	virtual ~Vengefly() {}

	virtual void Init() override;
	virtual void Update(float dt, Vector2f playerPos) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGround(FloatRect map) override;

	//const FloatRect GetGlobalBounds();	// �浹üũ �� �ʿ�
	bool UpdateCollision();	//  ���� ���� ����
	bool OnHitted(Time timeHit);	// ���� ���� ����

	virtual RectangleShape GetDetectShape() override;
	virtual void SetIsDetect(bool is) override;
};

