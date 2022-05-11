#pragma once
#include "../GameObject.hpp"

enum class Interaction_Type { NONE, DAMAGED, BROKEN, PORTAL, CHECKPOINT, BENCH, };

class Stable : public GameObject
{
protected:
	bool collidable;
	bool interactable;
	Interaction_Type type;
	int index_total;

public:
	Stable();
	virtual ~Stable();

	bool IsCollidable();
	bool IsInteractable();

	virtual Interaction_Type GetInteractionType();
	virtual void Interaction();
	virtual int GetIndexTotal();

	virtual void Init() override;
	virtual void Render(RenderWindow& window) override;
	virtual void Update(float dt) override;
	virtual bool Collision(GameObject* otherObj) override;
	virtual void Release() override;
};

class InvisibleWall : public Stable
{
private:
	RectangleShape wallShape;
public:
	InvisibleWall(float x, float y);
	virtual ~InvisibleWall();

	void SetSize(Vector2f size);
	void SetSize(float x, float y);

};
