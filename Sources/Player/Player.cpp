#include "Player.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/PlayerDataManager.hpp"

Player::Player()
	: isWay(true), isJump(true), isBottom(false), speed(200.f), isDash(false), isAttack(false), attackDelay(ATTACK_DELAY)
{
	hp = 0;
	mp = 0;
}

void Player::Init()
{
	hp = PlayerDataManager::GetInstance().GetPlayerHP();
	mp = PlayerDataManager::GetInstance().GetPlayerMP();

	SetTag(TAG::PLAYER);
	position.x = 1920 * 0.5f;
	position.y = 500.f;
	sprite.setPosition(position);
	//sprite.setOrigin(31, 0);
	// Animator 초기화
	animation.SetTarget(&sprite);

	// 공격 히트박스
	attackBox.setSize(Vector2f(140, 100));
	attackBox.setOrigin(Vector2f(0, 100));
	attackBoxPosition.x = position.x;
	attackBoxPosition.y = position.y - 10;
	attackBox.setPosition(attackBoxPosition);
	attackBox.scale(-1, 1);
	// 플레이어 히트박스
	hitBox.setSize(Vector2f(30, 80));
	hitBox.setOrigin(Vector2f(15, 80));
	attackBoxPosition.x = position.x;
	attackBoxPosition.y = position.y - 10;
	hitBox.setPosition(attackBoxPosition);
	hitBox.setFillColor(Color::Red);


	/**************************************************************************/

	rapidcsv::Document clips("data_tables/animations/player/player_animation_clips.csv");

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
			if (texMap.find(colTexure[i]) == texMap.end())
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

void Player::UpdateInput()
{

	// 큐로 받아놓고 선입력 처리

	// 좌우 입력시 이미지 방향 변화
	if (!isDash)
	{
		if (InputManager::GetInstance().GetKey(Keyboard::Right))
		{
			if (isWay)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				isWay = !isWay;
			}
		}
		if (InputManager::GetInstance().GetKey(Keyboard::Left))
		{
			if (!isWay)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				isWay = !isWay;
			}
		}
	}

	// 좌우 이동 -> 멈춤 이미지
	if ((InputManager::GetInstance().GetKeyUp(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyUp(Keyboard::Left)))
	{
		if (isBottom)
		{
			animation.Play("RunToIdle");
			animation.PlayQueue("Idle");
		}
	}
	// 좌우 이동 이미지
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyDown(Keyboard::Left))
	{
		if (isBottom)
		{
			animation.Play("StartMove");
			animation.PlayQueue("Move");
		}
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Z))
	{
		animation.Play("Jump");
		animation.PlayQueue("Jumping");

		isJump = true;
	}

	// 공격 이펙트 애니메이션 or 이전 이미지 저장하는 법????
	if (InputManager::GetInstance().GetKeyDown(Keyboard::X) && !isAttack)
	{
		animation.Play("Slash");
		animation.PlayQueue("Idle");	// 이전 이미지로
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::C) && !isDash)
	{
		animation.Play("Dash");
		animation.PlayQueue("Idle");	// 이전 이미지로
	}
}

void Player::Update(float dt, FloatRect tile)
{
	UpdateInput();

	Vector2f positionTemp = position;

	if (!isDash)
	{
		if (InputManager::GetInstance().GetKeyDown(Keyboard::C))
		{
			dashTemp = position;
			isDash = true;
		}
		// 좌우 키입력
		if (InputManager::GetInstance().GetKey(Keyboard::Right))
		{
			position.x += dt * speed;
		}
		if (InputManager::GetInstance().GetKey(Keyboard::Left))
		{
			position.x -= dt * speed;
		}
		// 점프 입력
		if (InputManager::GetInstance().GetKeyDown(Keyboard::Z) ||
			InputManager::GetInstance().GetKey(Keyboard::Z))
		{
			position.y -= dt * speed * 2.f;
			isBottom = false;
		}
		else
		{
			position.y += dt * speed * 2.f;
		}
		// 바닥 충돌 체크
		if ((float)position.y > tile.top &&
			((float)position.x > tile.left && (float)position.x < tile.left + tile.width))
		{
			if (isJump)
			{
				animation.Play("Idle");
				isJump = false;
			}
			position.y = positionTemp.y;
			isBottom = true;
		}
	}
	// 대쉬 입력
	if (isDash)
	{
		if (isWay)
		{
			if (position.x > dashTemp.x - 300.f)
			{
				position.x -= dt * speed * 5.f;
				position.y = dashTemp.y;
			}
			else
			{
				isDash = false;
			}
		}
		else
		{
			if (position.x < dashTemp.x + 300.f)
			{
				position.x += dt * speed * 5.f;
				position.y = dashTemp.y;
			}
			else
			{
				isDash = false;
			}
		}
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::X) && !isAttack)
	{
		isAttack = true;
	}
	attackDelay -= dt;
	if (attackDelay < 0.f)
	{
		attackDelay = ATTACK_DELAY;
		isAttack = false;
	}
	sprite.setPosition(position);
	// 공격 박스 포지션
	attackBoxPosition.x = position.x;
	attackBoxPosition.y = position.y - 10;
	attackBox.setPosition(attackBoxPosition);

	// 히트박스 포지션
	hitBox.setPosition(attackBoxPosition);

	animation.Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	if (isAttack)
	{
		window.draw(attackBox);
	}
	window.draw(sprite);
	window.draw(hitBox);
}

const FloatRect Player::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

int Player::GetHP()
{
	return hp;
}

int Player::GetMP()
{
	return mp;
}

void Player::AddHP(int value)
{
	hp += value;
}

void Player::AddMP(int value)
{
	mp += value;
}

bool Player::UpdateCollision()
{
	return false;	// 정의
}

bool Player::OnHitted(Time timeHit)
{
	return false;
}
