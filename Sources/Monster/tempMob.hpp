#pragma once
#include "../Objects/GameObject.hpp"

class tempMob : public GameObject
{
private:

public:
	tempMob() {}
	virtual ~tempMob() {}
	void Init();
	void Update(float dt);
	void Render(RenderWindow& window);
	void Release();
};

