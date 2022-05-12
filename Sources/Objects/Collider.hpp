#pragma once
#include "GameObject.hpp"

class Collider : public GameObject
{
public:
	Collider();
	Collider(Vector2f size, Vector2f pos);
	virtual ~Collider();

	virtual bool Collision(GameObject* otherObj);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(RenderWindow& window);
	virtual void Release();

	RectangleShape& GetShape();
};

