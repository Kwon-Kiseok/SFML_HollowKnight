#pragma once
#include "Monster.hpp"
#include "../../Sources/Animation/AnimationController.hpp"
#include "../../Sources/Managers/InputManager.hpp"

class Crawlid : public Monster
{
private:
	AnimationController animation;

	RectangleShape gavityShape;
	RectangleShape sideShape;

	Vector2f positionTemp;
	//Texture texture;
	std::map<std::string, Texture> texMap;

	const float GRAVITY = 1500.f;				// �߷�
	float gravity;								// �߷°��ӵ� ó��
public:
	Crawlid();
	Crawlid(int xdir);
	virtual ~Crawlid() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

	virtual void OnGround(FloatRect map) override;

	//const FloatRect GetGlobalBounds();	// �浹üũ �� �ʿ�
	bool UpdateCollision();	//  ���� ���� ����
	bool OnHitted(Time timeHit);	// ���� ���� ����
};

