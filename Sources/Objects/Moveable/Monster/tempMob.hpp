#pragma once
#include "Monster.hpp"
#include "../../Collider.hpp"
class tempMob : public Monster
{
private:
	Collider colliderBox;
public:
	tempMob() {}
	virtual ~tempMob() {}
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
};

