#pragma once
#include <SFML/Graphics.hpp>
#include "../Objects/GameObject.hpp"

using namespace sf;
class Item : public GameObject
{
public:
	Item();
	~Item();

	virtual bool Collision(GameObject* otherObj) override;
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(RenderWindow& window) override;
	virtual void Release() override;

};

