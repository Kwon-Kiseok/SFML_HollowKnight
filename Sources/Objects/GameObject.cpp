#include "GameObject.hpp"

GameObject::GameObject()
	:isVisible(true), layer(0), tag(TAG::NONE)
{
}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
}

void GameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(Vector2f(x, y));
}

Vector2f GameObject::GetPosition()
{
	return position;
}

Vector2f GameObject::GetOrigin()
{
	return sprite.getOrigin();
}

Texture& GameObject::GetTexture()
{
	return this->texture;
}

void GameObject::SetHidden()
{
	isVisible = false;
}

void GameObject::SetVisible()
{
	isVisible = true;
}

bool GameObject::GetIsVisible()
{
	return isVisible;
}

void GameObject::SetLayer(int layer)
{
	this->layer = layer;
}

int GameObject::GetLayer()
{
	return layer;
}

int GameObject::GetImageIdx()
{
	return imageIdx;
}

std::string& GameObject::GetName()
{
	return name;
}

void GameObject::SetTag(TAG tag)
{
	this->tag = tag;
}

void GameObject::SetName(std::string name)
{
	this->name = name;
}

TAG GameObject::GetTag()
{
	return tag;
}

bool GameObject::CompareTag(TAG tag)
{
	if (this->tag == tag)
		return true;
	return false;
}

void GameObject::SetTexture(std::string path)
{
	texture.loadFromFile(path);
}

void GameObject::SetSprite()
{
	sprite.setTexture(texture);
}

Sprite& GameObject::GetSprite()
{
	return sprite;
}

void GameObject::SetOriginCenter()
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void GameObject::DebugCollision(Vector2f size)
{
	rectangleShape.setSize(size);
	rectangleShape.setPosition(sprite.getPosition());
	rectangleShape.setOrigin(sprite.getOrigin());

	rectangleShape.setOutlineThickness(1.5f);
	rectangleShape.setOutlineColor(Color::Red);
	rectangleShape.setFillColor(Color::Color(0, 0, 0, 0));
}

bool GameObject::CollisionPoint(Vector2f point)
{
	if (boundingBox.contains(point))
		return true;
	return false;
}

bool GameObject::CollisionBox(FloatRect box)
{
	if (boundingBox.intersects(box))
		return true;
	return false;
}

bool GameObject::CheckCollision(GameObject* otherObj)
{
	return this->GetSprite().getGlobalBounds().intersects(otherObj->GetSprite().getGlobalBounds());
}
