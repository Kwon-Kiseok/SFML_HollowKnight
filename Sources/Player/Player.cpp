#include "Player.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/PlayerDataManager.hpp"

Player::Player()
	: isWay(true), isDash(false), isAttack(false), attackDelay(ATTACK_DELAY), gravity(GRAVITY)
{
	attackBox.scale(-1, 1);
	hp = 0;
	mp = 0;
	move = 0.f;
	jumpTime = JUMP_MAX;

}

void Player::Init()
{
	hp = PlayerDataManager::GetInstance().GetPlayerHP();
	mp = PlayerDataManager::GetInstance().GetPlayerMP();

	SetTag(TAG::PLAYER);
	SetName("Hero");
	sprite.setPosition(position);
	//sprite.setOrigin(31, 0);
	// Animator 초기화
	animation.SetTarget(&sprite);

	// 공격 히트박스
	attackBox.setSize(Vector2f(140, 100));
	attackBox.setOrigin(Vector2f(0, 110));
	attackBox.setPosition(position);
	attackBox.setFillColor(Color::Transparent);
	attackBox.setOutlineColor(Color::Yellow);
	attackBox.setOutlineThickness(2);
	// 플레이어 히트박스
	hitBox.setSize(Vector2f(30, 80));
	hitBox.setOrigin(Vector2f(15, 90));
	hitBox.setPosition(position);
	hitBox.setFillColor(Color::Transparent);
	hitBox.setOutlineColor(Color::Red);
	hitBox.setOutlineThickness(2);


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
	string = "Idle";

	effect.Init();
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
				SetDirection(Direction::RIGHT);
			}
		}
		if (InputManager::GetInstance().GetKey(Keyboard::Left))
		{
			if (!isWay)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				isWay = !isWay;
				SetDirection(Direction::LEFT);
			}
		}
	}

	// 좌우 이동 -> 멈춤 이미지
	if ((InputManager::GetInstance().GetKeyUp(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyUp(Keyboard::Left)))
	{
		animation.Play("RunToIdle");
		animation.PlayQueue("Idle");
	}
	// 좌우 이동 이미지
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyDown(Keyboard::Left))
	{
		animation.Play("StartMove");
		animation.PlayQueue("Move");
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Z))
	{
		animation.Play("Jump");
		animation.PlayQueue("Jumping");
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
		isDash = true;
		dashTemp = position;
	}
	/**********************************************
	**********************************************/
	if (InputManager::GetInstance().GetKey(Keyboard::Z))
	{
		gravity = -500.f;
	}
}

void Player::Update(float dt)
{
	positionTemp = position;
	Vector2f delta;

	/******************  knockback test  ****************/
	{
		if (isKnockback)
		{
			knockback -= dt;
			if (knockback > 0.f)
			{
				if (!isWay)
				{
					position.x -= 0.2f;
				}
				if (isWay)
				{
					position.x += 0.2f;
				}
			}
			else
			{
				isKnockback = false;
				knockback = 0.3f;
			}
		}
	}
	/******************  knockback test  ****************/

	/**********************************
	* 좌우 방향 이동
	**********************************/
	{

		float h = InputManager::GetInstance().GetAxisRaw(Axis::Horizontal);	// -1 0 1
		if (!isDash)
		{
			delta.x = h * SPEED * dt;
			if (!isWay && h == -1)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				isWay = !isWay;
				SetDirection(Direction::LEFT);
			}
			if (isWay && h == 1)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				isWay = !isWay;
				SetDirection(Direction::RIGHT);
			}
		}


		if (move == 0 && h != 0)
		{
			animation.Play("StartMove");
			animation.PlayQueue("Move");
			string = "Move";
		}
		if (move != 0 && h == 0)
		{
			animation.Play("RunToIdle");
			animation.PlayQueue("Idle");
			string = "Idle";
		}
		move = h;
	}
	/**********************************
	* 중력 및 점프
	**********************************/
	{
		gravity += GRAVITY * dt;
		//isFalling = false;
		if (gravity > 1000.f)
		{
			gravity = 1000.f;
		}
		if (InputManager::GetInstance().GetKey(Keyboard::Z) && canJump)
		{
			gravity = -700.f;
			isFalling = true;
			canJump = false;
		}

		if (isFalling)
		{
			delta.y = gravity * dt;
		}
	}
	/**********************************
	* 대쉬
	**********************************/
	{
		if (InputManager::GetInstance().GetKeyDown(Keyboard::C) && !isDash)
		{
			animation.Play("Dash");
			isDash = true;
			canJump = false;
			dashTemp = position;
		}
		if (isDash)
		{
			if (isWay)
			{
				position.x -= SPEED * dt * 5.f;
				position.y = dashTemp.y;
			}
			else
			{
				position.x += SPEED * dt * 5.f;
				position.y = dashTemp.y;
			}
			if (position.x < dashTemp.x - 500.f || position.x > dashTemp.x + 500.f)
			{
				isDash = false;
				canJump = true;
				animation.Play("RunToIdle");
				animation.PlayQueue(string);
				gravity = 0.f;
			}
		}
	}
	/**********************************
	* 공격
	**********************************/
	{
		if (InputManager::GetInstance().GetKeyDown(Keyboard::X) && !isAttack)
		{
			animation.Play("Slash");
			animation.PlayQueue(string);	// 이전 이미지로
			isAttack = true;
			effect.SetDraw("Slash");
		}
		attackDelay -= dt;
		if (attackDelay < 0.f)
		{
			attackDelay = ATTACK_DELAY;
			isAttack = false;
		}
	}


	position += delta;

	sprite.setPosition(position);
	attackBox.setPosition(position);
	hitBox.setPosition(position);

	animation.Update(dt);

	effect.Update(position);
}

void Player::Render(RenderWindow& window)
{
	if (isAttack)
	{
		window.draw(attackBox);
	}
	window.draw(sprite);
	window.draw(hitBox);

	effect.Draw(window);		// 왜 말을 안 듣니 너
}

void Player::Release()
{
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
	if (isAttack)
	{
		isAttack = false;
		isDash = false;
		isKnockback = true;
	}
	return false;
}

bool Player::OnHitted(Time timeHit)
{
	return false;
}

void Player::OnGround(float dt)
{
	gravity = 0.f;
	position.y = positionTemp.y;
	sprite.setPosition(position);
	isFalling = false;
	canJump = true;
}

const RectangleShape Player::GetAttackBox()
{
	return attackBox;
}

