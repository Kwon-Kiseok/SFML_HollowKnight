#include "Player.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Utils/Utility.hpp"


Player::Player()
	: isWay(true), isDash(false), isAttack(false), firstFrame(true), secondFrame(false), attackDelay(ATTACK_DELAY), gravity(GRAVITY)
{
	attackBox.scale(-1, 1);
	hp = 5;
	mp = 0;
	coin = 0;
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
	attackBox.setSize(Vector2f(140, 90));
	attackBox.setOrigin(Vector2f(0, 100));
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
	// 좌우 벽 충돌 처리
	hitBoxSide.setSize(Vector2f(40, 70));
	hitBoxSide.setOrigin(Vector2f(20, 85));
	hitBoxSide.setPosition(position);
	hitBoxSide.setFillColor(Color::Transparent);
	hitBoxSide.setOutlineColor(Color::Blue);
	hitBoxSide.setOutlineThickness(2);


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
	if (firstFrame)
	{
		if (secondFrame)
		{
			dt = 0.f;
			firstFrame = false;
		}
		dt = 0.f;
		secondFrame = true;
	}
	positionTemp = position;
	Vector2f delta;
	float h = InputManager::GetInstance().GetAxisRaw(Axis::Horizontal);	// -1 0 1
	float v = InputManager::GetInstance().GetAxisRaw(Axis::Vertical);	// -1 0 1

	/**********************************
	* 공격 방향 설정
	**********************************/
	if (!isAttack)
	{
		if (v == -1.f)
		{
			attackBox.setSize(Vector2f(140, 120));
			attackBox.setOrigin(Vector2f(70, 180));
			attackBox.setPosition(position);
			attackString = "UpSlash";
			effectString = "UpSlash";
		}
		else if (v == 1.f && !canJump)
		{
			attackBox.setSize(Vector2f(140, 140));
			attackBox.setOrigin(Vector2f(70, 50));
			attackBox.setPosition(position);
			attackString = "DownSlash";
			effectString = "DownSlash";
			knock = 1;
		}
		else
		{
			attackBox.setSize(Vector2f(140, 90));
			attackBox.setOrigin(Vector2f(0, 100));
			attackBox.setPosition(position);
			attackString = "Slash";
			effectString = "Slash";
			knock = 0;
		}
	}

	/******************  knockback test  ****************/
	/*{
		if (isKnockback)
		{
			knockbackTime -= dt;
			if (knock == 0)
			{
				if (knockbackTime > 0.f)
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
					knockbackTime = 0.3f;
				}
			}
		}
		else if (knock == 1 && isAttack)
		{
			gravity = -500.f;
			isKnockback = false;
		}
	}*/
	/******************  knockback test  ****************/

	/**********************************
	* 좌우 방향 이동
	**********************************/
	{

		if (!isDash)
		{
			delta.x = h * SPEED * dt * isMove;
			if (!isWay && h == -1)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				effect.SetScale();
				isWay = !isWay;
				SetDirection(Direction::LEFT);
			}
			if (isWay && h == 1)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				effect.SetScale();
				isWay = !isWay;
				SetDirection(Direction::RIGHT);
			}
		}


		if (move == 0 && h != 0)
		{
			animation.Play("StartMove");
			animation.PlayQueue("Move");
			string = "Move";
//
			SoundManager::GetInstance().PlaySound(L"walk");
		}
		if (move != 0 && h == 0)
		{
			animation.Play("RunToIdle");
			animation.PlayQueue("Idle");
			string = "Idle";
			SetDirection(Direction::NONE);
			SoundManager::GetInstance().GetSoundbyID(L"walk").stop();

		}
		move = h;
	}
	/**********************************
	* 중력 및 점프
	**********************************/
	{
		if (isFalling)
		{
			gravity += GRAVITY * dt;
		}
		isFalling = true;
		if (gravity > 1000.f)
		{
			gravity = 1000.f;
		}
		if (InputManager::GetInstance().GetKey(Keyboard::Z) && canJump)
		{
			SoundManager::GetInstance().PlaySound(L"jump");
			animation.Play("Jump");
			animation.PlayQueue("Jumping");
			gravity = -700.f;
			canJump = false;
		}
		delta.y = gravity * dt;
	}
	/**********************************
	* 대쉬
	**********************************/
	{
		if (InputManager::GetInstance().GetKeyDown(Keyboard::C) && !isDash)
		{

			SoundManager::GetInstance().PlaySound(L"dash");

			animation.Play("Dash");
			isDash = true;
			canJump = false;
			dashTemp = position;
		}
		if (isDash && isMove != 0)
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
				//animation.Play("RunToIdle");
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
			animation.Play(attackString);
			animation.PlayQueue(string);	// 이전 이미지로
			isAttack = true;
			effect.SetDraw("Slash");

			SoundManager::GetInstance().PlaySound(L"sword");
			effect.SetDraw(effectString);
		}
		attackDelay -= dt;
		if (attackDelay < 0.f)
		{
			attackDelay = ATTACK_DELAY;
			isAttack = false;
		}
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::G))
	{
		++coin;
	//	std::cout << coin << ", " << PlayerDataManager::GetInstance().GetPlayerCoin() << std::endl;
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::L))	//L: Life����
	{
		hp--;
	}

	else if (InputManager::GetInstance().GetKeyDown(Keyboard::P))	//P: Life��
	{
		hp++;
	}

	isMove = 1;
	position += delta;

	sprite.setPosition(position);
	attackBox.setPosition(position);
	hitBox.setPosition(position);
	hitBoxSide.setPosition(position);

	animation.Update(dt);

	effect.Update(position, dt);
}

void Player::Render(RenderWindow& window)
{
	if (isAttack)
	{
		effect.Draw(window);		// Slash
		window.draw(attackBox);
	}
	window.draw(sprite);
	window.draw(hitBox);
	window.draw(hitBoxSide);

}

void Player::Release()
{
}

const FloatRect Player::GetGlobalBounds()
{
	return hitBox.getGlobalBounds();
}

int Player::GetHP()
{
	return hp;
}

int Player::GetMP()
{
	return mp;
}

int Player::GetCoin()
{
	return coin;
}

void Player::AddHP(int value)
{
	hp += value;
}

void Player::AddMP(int value)
{
	mp += value;
}

void Player::AddCoin(int value)
{
	coin += value;
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

void Player::OnGround(FloatRect map)
{
	if (hitBox.getGlobalBounds().intersects(map))
	{
		if (!canJump)
		{
			animation.Play(string);
		}
		gravity = 0.f;
		position.y = positionTemp.y;
		if (InputManager::GetInstance().GetKeyDown(Keyboard::Z))
		{
			position.y -= 10.f;
		}
		canJump = true;
		isFalling = false;
	}
	if (hitBoxSide.getGlobalBounds().intersects(map))
	{
		isMove = 0;
		if (position.x < map.left)
		{
			if (InputManager::GetInstance().GetKeyDown(Keyboard::Left))
			{
				position.x -= 1.f;
			}
		}
		else if (position.x > map.width)
		{
			if (InputManager::GetInstance().GetKeyDown(Keyboard::Right))
			{
				position.x += 1.f;
			}
		}

		if (isDash)
		{
			isDash = false;
			animation.PlayQueue(string);
		}
	}
}

void Player::SetXpos()
{
	position.x = positionTemp.x;
}

//Vector2f Player::GetPosition()
//{
//	return position;
//}

const RectangleShape Player::GetAttackBox()
{
	return attackBox;
}

void Player::KnockBackSide()
{
	knockbackTime -= 0.001f;
	if (knockbackTime > 0.f)
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
		knockbackTime = 0.3f;
	}
}

void Player::KnockBackUp()
{
	gravity = -500.f;
}

