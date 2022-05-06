#pragma once
#include "../GameObject.hpp"

enum class Interaction_Type { NONE, DAMAGED, BROKEN, PORTAL };

class Stable : public GameObject
{
protected:
	bool collidable;
	bool interactable;
	Interaction_Type type;

public:
	Stable();
	virtual ~Stable();

	bool IsCollidable();
	bool IsInteractable();

	virtual Interaction_Type GetInteractionType();
	virtual void Interaction();

	virtual void Init() override;
	virtual void Render(RenderWindow& window) override;
	virtual void Update(float dt) override;
	virtual bool Collision(GameObject* otherObj) override;
	virtual void Release() override;
};

