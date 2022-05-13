#include "FalseKnight.hpp"
#include "../../Sources/Animation/rapidcsv.hpp"
#include "../../Sources/Managers/TextureManager.hpp"
#include "../../Sources/Utils/Utility.hpp"
#include <cstdlib>

FalseKnight::FalseKnight()
{
	moveSpeed = 100.f;
	health = 3;
	shield = 1;
	isShield = true;
	downTime = 2.f;
}

FalseKnight::FalseKnight(int xdir)
{
	moveSpeed = 100.f;
	health = 3;
	shield = 1;
	isShield = true;
	downTime = 2.f;
}

void FalseKnight::Init()
{
	srand((int)time(NULL));												// 난수 생성

	SetName("boss");
	SetTag(TAG::MONSTER);
	texture.loadFromFile("Resources/Sprite/Monster/boss/idle.png");
	sprite.setTexture(texture);
	sprite.setPosition(position);
	sprite.setOrigin(Vector2f(350, 600));

	rectangleShape.setSize(Vector2f(300, 300));
	rectangleShape.setOrigin(Vector2f(150, 300));
	rectangleShape.setPosition(position);
	rectangleShape.setFillColor(Color::Transparent);
	rectangleShape.setOutlineColor(Color::Red);
	rectangleShape.setOutlineThickness(2);

	attackBox.setSize(Vector2f(100, 100));
	attackBox.setOrigin(Vector2f(270, 170));
	attackBox.setPosition(position);
	attackBox.setFillColor(Color::Transparent);
	attackBox.setOutlineColor(Color::Yellow);
	attackBox.setOutlineThickness(2);

	detectShape.setSize(Vector2f(600, 300));
	detectShape.setOrigin(Vector2f(300, 300));
	detectShape.setPosition(position);
	detectShape.setFillColor(Color::Transparent);
	detectShape.setOutlineColor(Color::Blue);
	detectShape.setOutlineThickness(2);
}

void FalseKnight::Update(float dt, Vector2f player)
{
	/********************************
	* 공격 패턴
	*********************************/
	if (isDetect && isShield && isAlive)
	{
		gravity -= 50.f;
		/*int random = (rand() % 3) + 1;
		std::cout << random << std::endl;
		switch (random)
		{
		case 1:
			gravity -= 500.f;
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}*/
		isDetect = !isDetect;
	}
	/****************************
	* 중력 처리
	*****************************/
	if (isFalling)
	{
		gravity += GRAVITY * dt;
		if (gravity > 1000.f)
		{
			gravity = 1000.f;
		}
		position.y += gravity * dt;
	}
	isFalling = true;
	/********************************
	* 플레이어 추격 및 이동
	*********************************/
	if (!isDetect)
	{
		if (isAlive && isShield)
		{
			if (position.x < player.x)
			{
				xDir = 1;
				sprite.setScale(1, 1);
				attackBox.setScale(1, 1);
			}
			if (position.x > player.x)
			{
				xDir = -1;
				sprite.setScale(-1, 1);
				attackBox.setScale(-1, 1);
			}
			position.x += (moveSpeed * dt) * xDir;
		}
	}
	


	/****************************
	* 쉴드 처리
	*****************************/
	if (!isShield)
	{
		downTime -= dt;
	}
	if (downTime < 0.f)
	{
		shield = 1;
		downTime = 2.f;
		isShield = true;
		texture.loadFromFile("Resources/Sprite/Monster/boss/idle.png");
		sprite.setTexture(texture);
		rectangleShape.setSize(Vector2f(300, 300));
		rectangleShape.setOrigin(Vector2f(150, 300));
	}
	if (shield == 0)
	{
		isShield = false;
		texture.loadFromFile("Resources/Sprite/Monster/boss/down.png");
		sprite.setTexture(texture);
		rectangleShape.setSize(Vector2f(75, 75));
		if (xDir > 0)
		{
			rectangleShape.setOrigin(Vector2f(-115, 75));
		}
		else
		{
			rectangleShape.setOrigin(Vector2f(190, 75));
		}
	}
	/****************************
	* 체력 처리
	*****************************/
	if (health == 0)
	{
		isAlive = false;
		texture.loadFromFile("Resources/Sprite/Monster/boss/die.png");
		sprite.setTexture(texture);
	}




	sprite.setPosition(position);
	rectangleShape.setPosition(position);
	attackBox.setPosition(position);
	detectShape.setPosition(position);	
}

void FalseKnight::Render(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(rectangleShape);
	window.draw(attackBox);
	window.draw(detectShape);
}

void FalseKnight::Release()
{
}

void FalseKnight::OnGround(FloatRect map)
{
	if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > map.left + map.width ||
		sprite.getGlobalBounds().left < map.left)
	{
		xDir = -xDir;
		sprite.scale(-1, 1);
	}

	if (rectangleShape.getGlobalBounds().intersects(map))
	{
		if (rectangleShape.getGlobalBounds().intersects(map))
		{
			Pivots pivot = Utility::CollisionDir(map, rectangleShape.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				sprite.setScale(-1, 1);
				xDir = 1;
				break;

			case Pivots::RC:
				sprite.setScale(1, 1);
				xDir = -1;
				break;

			case Pivots::CT:
				gravity = 0.f;
				position.y += (map.top + map.height) - (rectangleShape.getGlobalBounds().top);
				InputManager::GetInstance().HorizontalInit();
				//InputManager::VerticalInit();
				break;

			case Pivots::CB:
				gravity = 0.f;
				position.y -= (rectangleShape.getGlobalBounds().top + rectangleShape.getGlobalBounds().height) - (map.top);
				InputManager::GetInstance().HorizontalInit();
				break;
			defalut:
				break;
			}
		}
	}
}

bool FalseKnight::OnHitted(Time timeHit)
{
	if (health == 0)
	{
		PlayerDataManager::GetInstance().AddCoin(3);
	}
	return false;
}

void FalseKnight::SetShield(int _shield)
{
	shield += _shield;
}

RectangleShape FalseKnight::GetDetectShape()
{
	return detectShape;
}

void FalseKnight::SetIsDetect(bool is)
{
	isDetect = is;
}
