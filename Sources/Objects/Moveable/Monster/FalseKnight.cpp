#include "FalseKnight.hpp"
#include "../../Sources/Animation/rapidcsv.hpp"
#include "../../Sources/Managers/TextureManager.hpp"
#include "../../Sources/Utils/Utility.hpp"
#include <cstdlib>

FalseKnight::FalseKnight()
{
	moveSpeed = 100.f;
	health = 3;
	shield = SHIELD;
	isShield = true;
	downTime = DOWNTIME;

	attackDelay = -1.f;
}

FalseKnight::FalseKnight(int xdir)
{
	moveSpeed = 100.f;
	health = 3;
	shield = SHIELD;
	isShield = true;
	downTime = DOWNTIME;

	attackDelay = -1.f;
}

void FalseKnight::Init()
{
	srand((int)time(NULL));												// 난수 생성

	SetName("boss");
	SetTag(TAG::MONSTER);
	SetLayer(5);
	animation.SetTarget(&sprite);
	/***************************
	* 히트 박스
	****************************/
	{
		rectangleShape.setSize(Vector2f(500, 300));
		rectangleShape.setOrigin(Vector2f(250, 300));
		rectangleShape.setPosition(position);
		rectangleShape.setFillColor(Color::Transparent);
		rectangleShape.setOutlineColor(Color::Red);
		rectangleShape.setOutlineThickness(2);
	}
	/***************************
	* 공격 박스
	****************************/
	{
		attackBox.setSize(Vector2f(100, 100));
		attackBox.setOrigin(Vector2f(270, 270));
		attackBox.setPosition(position);
		attackBox.setFillColor(Color::Transparent);
		attackBox.setOutlineColor(Color::Yellow);
		attackBox.setOutlineThickness(2);
	}
	/***************************
	* 감지 박스
	****************************/
	{
		detectShape.setSize(Vector2f(600, 300));
		detectShape.setOrigin(Vector2f(300, 300));
		detectShape.setPosition(position);
		detectShape.setFillColor(Color::Transparent);
		detectShape.setOutlineColor(Color::Blue);
		detectShape.setOutlineThickness(2);
	}
	/***************************
	* Wave Sprite
	****************************/
	{
		texture.loadFromFile("Resources/Sprite/Monster/boss/wave.png");
		waveSprite.setTexture(texture);
	}

	rapidcsv::Document clips("data_tables/animations/falseknight/falseknight_animation_clips.csv");

	std::vector<std::string> colId = clips.GetColumn<std::string>("ID");
	std::vector<int> colFps = clips.GetColumn<int>("FPS");
	std::vector<int> colLoop = clips.GetColumn<int>("LOOP TYPE(0:Single, 1:Loop)");
	std::vector<std::string> colPath = clips.GetColumn<std::string>("CLIP PATH");

	int totalClips = colId.size();
	for (int i = 0; i < totalClips; ++i)
	{
		AnimationClip clip;
		clip.id = colId[i];
		clip.fps = colFps[i];
		clip.loopType = (AnimationLoopTypes)colLoop[i];

		rapidcsv::Document frames(colPath[i]);
		std::vector<std::string> colTexure = frames.GetColumn<std::string>("TEXTURE PATH");
		std::vector<int> colL = frames.GetColumn<int>("L");
		std::vector<int> colT = frames.GetColumn<int>("T");
		std::vector<int> colW = frames.GetColumn<int>("W");
		std::vector<int> colH = frames.GetColumn<int>("H");

		std::vector<int> colX = frames.GetColumn<int>("X");
		std::vector<int> colY = frames.GetColumn<int>("Y");

		int totalFrames = colTexure.size();
		for (int j = 0; j < totalFrames; ++j)
		{
			if (texMap.find(colTexure[j]) == texMap.end())
			{
				auto& ref = texMap[colTexure[j]];
				ref.loadFromFile(colTexure[j]);
			}
			clip.frames.push_back(AnimationFrame(texMap[colTexure[j]], IntRect(colL[j], colT[j], colW[j], colH[j]), Vector2f(colX[j], colY[j])));
		}
		animation.AddClip(clip);
	}

	animation.Play("Idle");
}

void FalseKnight::Update(float dt, Vector2f player)
{
	if (lodingTime > 0.f)
	{
		lodingTime -= dt;
		gravity = 0.f;
	}

	
	Attack(dt);

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
	{
		if (!isDetect)
		{
			if (isAlive && isShield)
			{
				if (position.x < player.x)
				{
					xDir = 1;
					sprite.setScale(1, 1);
					attackBox.setScale(1, 1);
					rectangleShape.setScale(1, 1);
					waveSprite.setScale(1, 1);
				}
				if (position.x > player.x)
				{
					xDir = -1;
					sprite.setScale(-1, 1);
					attackBox.setScale(-1, 1);
					rectangleShape.setScale(-1, 1);
					waveSprite.setScale(-1, 1);
				}
				position.x += (moveSpeed * dt) * xDir;
			}
		}
	}
	/****************************
	* 쉴드 처리
	*****************************/
	if (isAlive)
	{
		if (!isShield)
		{
			downTime -= dt;
		}
		if (downTime < 0.f)
		{
			shield = SHIELD;
			downTime = DOWNTIME;
			isShield = true;
			animation.Play("Idle");
			rectangleShape.setSize(Vector2f(500, 300));
			rectangleShape.setOrigin(Vector2f(250, 300));
			attackDelay = ATTACK_DELAY * 0.5f;
		}
		/******************
		* 스턴 판정
		*******************/
		if (shield == 0)
		{
			isOne = true;
			shield = -1;
		}
		if (isOne)
		{
			isShield = false;
			animation.Play("Stun");
			rectangleShape.setSize(Vector2f(100, 100));
			rectangleShape.setOrigin(Vector2f(170, 100));
			if (xDir > 0)
			{
				rectangleShape.setScale(-1, 1);
			}
			else
			{
				rectangleShape.setScale(1, 1);
			}
			isOne = false;
		}
	}
	/****************************
	* 체력 처리
	*****************************/
	{
		if (health == 0)
		{
			animation.Stop();
			isAlive = false;
		}
	}




	sprite.setPosition(position);
	rectangleShape.setPosition(position);
	attackBox.setPosition(attackBoxPos);
	detectShape.setPosition(position);

	animation.Update(dt);
}

void FalseKnight::Render(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(rectangleShape);
	window.draw(detectShape);
	if (isAttack)
	{
		if (attackPattern == 3 && attackDelay < 3.f)
		{
			window.draw(waveSprite);
		}
	}
	window.draw(attackBox);
}

void FalseKnight::Release()
{
}

void FalseKnight::OnGround(FloatRect map)
{
	if (rectangleShape.getGlobalBounds().intersects(map))
	{
		if (rectangleShape.getGlobalBounds().intersects(map))
		{
			Pivots pivot = Utility::CollisionDir(map, rectangleShape.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				position.x += (map.left + map.width) - (rectangleShape.getGlobalBounds().left);
				InputManager::GetInstance().HorizontalInit();
				break;
			case Pivots::RC:
				position.x -= (rectangleShape.getGlobalBounds().left + rectangleShape.getGlobalBounds().width) - (map.left);
				InputManager::GetInstance().HorizontalInit();
				break;
			case Pivots::CT:
				gravity = 0.f;
				position.y += (map.top + map.height) - (rectangleShape.getGlobalBounds().top);
				InputManager::GetInstance().HorizontalInit();
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

//RectangleShape FalseKnight::GetAttackShape()
//{
//	return attackBox;
//}
/****************************************************************
* 공격 패턴
*****************************************************************/
void FalseKnight::Attack(float dt)
{	
	attackDelay -= dt;
	if (isAttack)
	{
		position.x += (moveSpeed * dt) * xDir;
		if (attackDelay < 3.f)
		{
			//attackPattern = 3;
			if (attackPattern == 1)
			{
				attackBox.setSize(Vector2f(100, 400));
				attackBox.setOrigin(Vector2f(-200, 400));
			}
			if (attackPattern == 2)
			{
				attackDelay -= dt;
				attackBox.setSize(Vector2f(100, 400));
				attackBox.setOrigin(Vector2f(-200, 400));
			}
			if (attackPattern == 3)
			{
				attackBox.setSize(Vector2f(300, 300));
				attackBox.setOrigin(Vector2f(-200, 300));
				attackBoxPos.x += 1000.f * dt * attackDir;
				moveSpeed = 0.f;

				waveSprite.setOrigin(Vector2f(-200, 300));
				waveSprite.setPosition(attackBoxPos);
			}

			if (attackDelay <= 2.f)
			{
				isAttack = false;
				attackBox.setSize(Vector2f(100, 100));
				attackBox.setOrigin(Vector2f(270, 270));
				moveSpeed = 100.f;
				attackBoxPos = position;
				isDetect = !isDetect;

				attackPattern = 0;
			}
		}
	}
	if (attackPattern != 3)
	{
		attackBoxPos = position;
	}
	int wave = (rand() % 10000) + 1;
	if (wave == 1)
	{
		isDetect = true;
	}
	if (isDetect && isShield && isAlive)
	{
		int random = (rand() % 3) + 1;
		if (wave == 1)
		{
			random = 3;
		}
		if (attackDelay < 0.f)
		{
			attackDelay = ATTACK_DELAY;
			isAttack = true;
			attackDir = xDir;
			switch (random)
			{
			case 1:	// 점프 공격
				animation.Play("Jump");
				animation.PlayQueue("JumpAttack");
				animation.PlayQueue("Idle");
				gravity -= 1200.f;

				attackPattern = 1;
				break;
			case 2: // 기본 공격
				animation.Play("Attack");
				animation.PlayQueue("Idle");

				attackBox.setSize(Vector2f(500, 300));
				attackBox.setOrigin(Vector2f(250, 600));

				attackPattern = 2;
				break;
			case 3:	// 충격파
				animation.Play("Attack");
				animation.PlayQueue("Idle");

				attackBox.setSize(Vector2f(500, 300));
				attackBox.setOrigin(Vector2f(250, 600));

				moveSpeed = 0.f;
				attackPattern = 3;
				break;
			}
		}
		isDetect = !isDetect;
	}
}
