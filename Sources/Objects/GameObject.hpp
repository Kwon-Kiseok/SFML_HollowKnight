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

	// Set Function
	void SetTexture(std::string path);
	void SetSprite();
	void SetPosition(Vector2f pos);
	void SetPosition(float x, float y);
	void SetOriginCenter();
	void SetVisible();
	void SetHidden();
	void SetLayer(int layer);
	void SetTag(TAG tag);

	// Get Function
	Vector2f GetPosition();
	Texture& GetTexture();
	Sprite& GetSprite();
	TAG GetTag();
	bool GetIsVisible();
	int GetLayer();

	// 
	bool CompareTag(TAG tag);
	
	void DebugCollision(Vector2f size);
	bool CollisionPoint(Vector2f point);
	bool CollisionBox(FloatRect box);

	virtual bool CheckCollision(GameObject* otherObj);
	virtual bool Collision(GameObject* otherObj) = 0;

	//
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(RenderWindow& window) = 0;
	virtual void Release() = 0;
};

