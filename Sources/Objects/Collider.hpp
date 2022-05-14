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
	virtual void SetPosition(Vector2f pos) override;
	virtual void SetPosition(float x, float y) override;
	virtual void SetOriginCenter() override;
};

