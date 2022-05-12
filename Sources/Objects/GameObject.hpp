#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

enum class TAG
{
	NONE,
	PLAYER,
	MONSTER,
	COLLIDER,
	GROUND,
	BENCH,
	BACKGROUND,
	TRAP,
	BREAKABLE,
	COIN,
};

class GameObject
{
protected:
	Texture texture;
	Sprite sprite;
	Vector2f position;
	int layer;
	TAG tag;
	std::string name;
	bool isVisible;

	int imageIdx;

	RectangleShape rectangleShape;
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
	void SetName(std::string name);

	// Get Function
	Vector2f GetPosition();
	Vector2f GetOrigin();
	Texture& GetTexture();
	Sprite& GetSprite();
	RectangleShape& GetRectangleShape();
	TAG GetTag();
	bool GetIsVisible();
	int GetLayer();
	int GetImageIdx();
	std::string& GetName();

	// 
	bool CompareTag(TAG tag);
	
	void DebugCollision();

	virtual bool CheckCollision(GameObject* otherObj);
	virtual bool Collision(GameObject* otherObj) = 0;

	//
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(RenderWindow& window) = 0;
	virtual void Release() = 0;
};

