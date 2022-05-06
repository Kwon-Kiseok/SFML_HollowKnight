#pragma once
#include "Monster.hpp"

class tempMob : public Monster
{
private:

public:
	tempMob() {}
	virtual ~tempMob() {}
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;
};

