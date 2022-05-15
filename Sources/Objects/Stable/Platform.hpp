#pragma once
#include "Stable.hpp"

class Collider;
enum class PLATFORM_TYPE
{
	FIXED,
	ELEVEATOR,
	SIDEMOVE,
	FALLEN,
};

class Platform : public Stable
{
private:
	Vector2f startPos;
	Vector2f endPos;
	float speed;
	int direction;

	Collider* collider;
	bool elevatorTrigger;
	PLATFORM_TYPE platformType;
public:
	Platform();
	Platform(int idx);
	virtual ~Platform();

	virtual void Update(float dt) override;

	void SetElevator(float endPos, int dir, float speed);
	void Elevate(float dt);
	Collider* GetCollider();
	virtual void Interaction(Player& player) override;
};
