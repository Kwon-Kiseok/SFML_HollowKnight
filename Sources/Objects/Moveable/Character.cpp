#include "Character.hpp"

Character::Character()
{
	canFall = false;
	canJump = true;
	canMove = true;
	currentDir = Direction::NONE;
	prevDir = Direction::NONE;
	deltaTime = 0.f;
	gravity = 980.f;
	health = 10;

	isColliding = false;
	isFalling = false;
	isJumping = false;

	jumpSpeed = 3.f;
	moveSpeed = 5.f;

	state = State::IDLE;

	xDir = 0;
	yDir = 0;
}

Character::~Character()
{
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

bool Character::Collision_AttackBox(RectangleShape& attackBox)
{
	return this->sprite.getGlobalBounds().intersects(attackBox.getGlobalBounds());
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

void Character::OnGround(FloatRect map)
{
}
