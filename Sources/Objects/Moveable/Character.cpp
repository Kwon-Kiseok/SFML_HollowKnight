#include "Character.hpp"
#include "../../Utils/Utility.hpp"

Character::Character()
{
	isAlive = true;
	canFall = false;
	canJump = true;
	canMove = true;
	currentDir = Direction::NONE;
	colDir = Vector2f(0.f, 0.f);
	deltaTime = 0.f;
	gravity = 980.f;
	health = 0;
	

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

Vector2f& Character::SetColDirection(GameObject* otherObj)
{
	colDir.x = this->position.x - otherObj->GetPosition().x;
	colDir.y = this->position.y - otherObj->GetPosition().y;

	colDir = Utility::Normalize(colDir);

	return colDir;
}

Vector2f& Character::GetColDirection()
{
	return colDir;
}

Direction Character::GetDirection()
{
	return currentDir;
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
	this->health += health;
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

bool Character::GetIsAlivve()
{
	return isAlive;
}
