#include "Character.hpp"

Character::Character()
{
	canFall = false;
	canJump = true;
	canMove = true;
	currentDir = Direction::NONE;
	prevDir = Direction::NONE;
	deltaTime = 0.f;
	gravity = 2.f;
	health = 10;

	isColliding = false;
	isFalling = false;
	isJumping = false;

	jumpSpeed = 3.f;
	moveSpeed = 5.f;
	name = "Default";
}

Character::~Character()
{
}

std::string Character::GetName()
{
	return name;
}

int Character::GetHealth()
{
	return health;
}

Direction Character::GetPrevDirection()
{
	return prevDir;
}

void Character::SetX(float x)
{
	this->position.x = x;
}

void Character::SetY(float y)
{
	this->position.y = y;
}

void Character::SetName(std::string name)
{
	this->name = name;
}

void Character::SetHealth(int health)
{
	this->health = health;
}

void Character::SetDirection(Direction dir)
{
	this->currentDir = dir;
}

void Character::SetCollisionState(bool isCol)
{
	this->isColliding = isCol;
}

void Character::Move(Vector2f newPosition)
{
	this->sprite.setPosition(newPosition);
}

bool Character::Collision(GameObject* otherObj)
{
	return this->GetSprite().getGlobalBounds().intersects(otherObj->GetSprite().getGlobalBounds());
}

void Character::Init()
{
}

void Character::Update(float dt)
{
}

void Character::Render(RenderWindow& window)
{
}

void Character::Release()
{
}
