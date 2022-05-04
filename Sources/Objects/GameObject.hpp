#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class TAG
{
	NONE,
	PLAYER,
	MONSTER,
	GROUND,
	BACKGROUND,
	TRAP,
	BREAKABLE,
};

class GameObject
{
protected:
	Texture texture;
	Sprite sprite;
	Vector2f position;
	int layer;
	TAG tag;
	bool isVisible;

	RectangleShape rectangleShape;
	FloatRect boundingBox;
public:
	GameObject();
	virtual ~GameObject();

	void SetPosition(Vector2f pos);
	Vector2f GetPosition();

	void SetHidden();
	void SetVisible();
	bool GetIsVisible();

	void SetLayer(int layer);
	int GetLayer();

	void SetTag(TAG tag);
	TAG GetTag();
	bool CompareTag(TAG tag);

	void SetTexture(std::string path);
	void SetSprite();
	Sprite GetSprite();
	void SetOriginCenter();
	
	void DebugCollision(Vector2f size);
	bool CollisionPoint(Vector2f point);
	bool CollisionBox(FloatRect box);


};

