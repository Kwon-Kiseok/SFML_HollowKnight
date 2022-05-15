#include "Player.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Managers/InputManager.hpp"
#include "../Managers/PlayerDataManager.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Utils/Utility.hpp"
#include "../Objects/Stable/Stable.hpp"
#include "../Objects/Stable/Portal.hpp"

Player::Player()
	: isWay(true), isDash(false), isAttack(false), hitAttack(false), attackDelay(ATTACK_DELAY), gravity(GRAVITY)
{
	attackBox.scale(-1, 1);
	health = 5;
	mp = 0;
	coin = 0;
	move = 0.f;
	jumpTime = JUMP_MAX;
	jumpTime = 0.f;
	collisionTime = 1.f;
	knockbackTime = 0.3f;

	slowTick = 0;
	knockbackX = 0.f;
}

void Player::Init()
{
	health = PlayerDataManager::GetInstance().GetPlayerHP();
	mp = PlayerDataManager::GetInstance().GetPlayerMP();

	SetTag(TAG::PLAYER);
	SetName("Hero");
	sprite.setPosition(position);
	SetLayer(5);
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
	/*hitBoxSide.setSize(Vector2f(50, 70));
	hitBoxSide.setOrigin(Vector2f(25, 85));
	hitBoxSide.setPosition(position);
	hitBoxSide.setFillColor(Color::Transparent);
	hitBoxSide.setOutlineColor(Color::Blue);
	hitBoxSide.setOutlineThickness(2);*/


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
	animation.SetSpeed(1.5f);
	animation.Play("Idle");
	string = "Idle";

	effect.Init();
	dashDffect.Init();
}

void Player::Update(float dt)
{
	
	if (lodingTime > 0.f)
	{
		lodingTime -= dt;
		gravity = 0.f;
	}

	positionTemp = position;
	collisionTime -= dt; // 맞는거 딜레이를 위해서 필요함	

	if (knockbackX < 0.f)
	{
		knockbackX += dt;
		if (knockbackX > 0.f)
		{
			knockbackX = 0.f;
		}
	}
	else if (knockbackX > 0.f)
	{
		knockbackX -= dt;
		if (knockbackX < 0.f)
		{
			knockbackX = 0.f;
		}
	}


	Vector2f delta;

	float h = InputManager::GetInstance().GetAxisRaw(Axis::Horizontal);	// -1 0 1
	float v = InputManager::GetInstance().GetAxisRaw(Axis::Vertical);	// -1 0 1

	/**********************************
	* 공격 방향 설정
	**********************************/
	
	{
		if (v == -1.f)
		{
			attackBox.setSize(Vector2f(140, 120));
			attackBox.setOrigin(Vector2f(70, 180));
			attackBox.setPosition(position);
			attackString = "UpSlash";
			effectString = "UpSlash";
			AttackDir = -1;
		}
		else if (v == 1.f && !canJump)
		{
			attackBox.setSize(Vector2f(140, 140));
			attackBox.setOrigin(Vector2f(70, 50));
			attackBox.setPosition(position);
			attackString = "DownSlash";
			effectString = "DownSlash";
			AttackDir = 1;
		}
		else
		{
			attackBox.setSize(Vector2f(140, 90));
			attackBox.setOrigin(Vector2f(0, 100));
			attackBox.setPosition(position);
			attackString = "Slash";
			effectString = "Slash";
			AttackDir = 0;
		}
		
	}
	/******************  knockback test  ****************/
	{
		if (isKnockback)
		{
			if (AttackDir == 0)
			{
				if (collisionType == 0 || collisionType == 1)
				{
					knockbackTime -= dt;
					if (knockbackTime > 0.f)
					{
						if (!isWay)
						{
							position.x -= 0.4f;
						}
						if (isWay)
						{
							position.x += 0.4f;
						}
					}
					else
					{
						isKnockback = false;
						knockbackTime = 0.3f;
					}
				}
			}
			else if (AttackDir == 1)
			{
				if (collisionType == 0 || collisionType == 2)
				{
					gravity = -700.f;
					AttackDir = -1;
					isKnockback = false;
				}
			}
		}
	}
	/******************  knockback test  ****************/
	/**********************************
	* 좌우 방향 이동
	**********************************/
	
	{

		if (!isDash)
		{
			delta.x = h * SPEED * dt;
			if (!isWay && h == -1)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				effect.SwapScale();
				dashDffect.SwapScale();
				isWay = !isWay;
				SetDirection(Direction::LEFT);
			}
			if (isWay && h == 1)
			{
				sprite.scale(-1, 1);
				attackBox.scale(-1, 1);
				effect.SwapScale();
				dashDffect.SwapScale();
				isWay = !isWay;
				SetDirection(Direction::RIGHT);
			}
		} 

		if (canJump)
		{
			if (move == 0 && h != 0)
			{
				animation.Play("StartMove");
				animation.PlayQueue("Move");
				string = "Move";
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
	}
	/**********************************
	* 중력 및 점프
	**********************************/
	
	{
		if (isFalling && lodingTime < 0.f)
		{
			gravity += GRAVITY * dt;
		}
		isFalling = true;
		if (gravity > 1000.f)
		{
			gravity = 1000.f;
		}

			if (InputManager::GetInstance().GetKeyDown(Keyboard::Z) && canJump)
			{
				SoundManager::GetInstance().PlaySound(L"jump");
				animation.Play("Jump");
				animation.PlayQueue("Jumping");
				gravity = -500.f;
				canJump = false;
			}
			if (InputManager::GetInstance().GetKeyUp(Keyboard::Z))
			{
				jumpTime = 0.5f;
			}
			if (InputManager::GetInstance().GetKey(Keyboard::Z))
			{
				jumpTime += dt;
				if (jumpTime < 0.5f)
				{
					gravity -= GRAVITY * dt * 1.2f;
				}
			}
		
		delta.y = gravity * dt;
	}
	/**********************************
	* 대쉬
	**********************************/
	
	{
		dashDelay -= dt;
		if (dashDelay < 0.f)
		{
			if (InputManager::GetInstance().GetKeyDown(Keyboard::C) && !isDash && canDash)
			{
				SoundManager::GetInstance().PlaySound(L"dash");
				gravity = 0.f;
				animation.Play("Dash");
				isDash = true;
				dashTemp = position;
				canDash = false;
				dashDelay = 0.6f;
				dashDffect.SetDraw("Dash");
			}
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
			if (position.x < dashTemp.x - 400.f || position.x > dashTemp.x + 400.f)
			{
				isDash = false;
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
			hitAttack = true;

			SoundManager::GetInstance().PlaySound(L"sword");
			effect.SetDraw(effectString);

		}
		attackDelay -= dt;
		if (attackDelay < 0.f)
		{
			attackDelay = ATTACK_DELAY;
			isAttack = false;
			hitAttack = false;
		}
	}

	// 체력 회복
	if (InputManager::GetInstance().GetKey(Keyboard::A) && (health < 5))	//P: Life��
	{
		healDeltaTime += dt;

		if (healDeltaTime >= 2.f)
		{
			health++;
			healDeltaTime = 0;
			return;
		}
	}

	if (knockbackX != 0.f)
	{
		delta.x += knockbackX;
	}
	position += delta;

	sprite.setPosition(position);
	attackBox.setPosition(position);
	hitBox.setPosition(position);
	//hitBoxSide.setPosition(position);

	animation.Update(dt);

	effect.Update(position, dt);
	dashDffect.Update(position, dt);
}

void Player::Render(RenderWindow& window)
{
	window.draw(sprite);

	if (MapManager::GetInstance().GetIsDebugMode())
	{
		if (isAttack)
		{
			window.draw(attackBox);
		}
		window.draw(hitBox);
		//window.draw(hitBoxSide);
	}
	effect.Draw(window);		// Slash
	if (isDash)
	{
		dashDffect.Draw(window);
	}
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
	return health;
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
	health += value;
}

void Player::AddMP(int value)
{
	mp += value;
}

void Player::AddCoin(int value)
{
	coin += value;
}

void Player::UpdateCollision(int type)
{
	if (isAttack)
	{
		isDash = false;
		isKnockback = true;
		collisionType = type;
	}
}

void Player::OnHitted(Vector2f pos)
{
	isDash = false;
	slowTick = 0;

	if (collisionTime < 0.f)
	{
		gravity = -500.f;
		if (position.x > pos.x)
		{
			knockbackX = 1.5f;
		}
		else if (position.x < pos.x)
		{
			knockbackX = -1.5f;
		}
		animation.Play("Stun");
	}
}

void Player::OnGround(FloatRect map)
{
	if (hitBox.getGlobalBounds().intersects(map))
	{
		if (hitBox.getGlobalBounds().intersects(map))
		{
			Pivots pivot = Utility::CollisionDir(map, hitBox.getGlobalBounds());

			switch (pivot)
			{
			case Pivots::LC:
				if (isDash && hitBox.getGlobalBounds().top + hitBox.getGlobalBounds().height - 5.f < map.top)
				{
					break;
				}
				position.x += (map.left + map.width) - (hitBox.getGlobalBounds().left);
				InputManager::GetInstance().HorizontalInit();
				isDash = false;
				break;

			case Pivots::RC:
				if (isDash && hitBox.getGlobalBounds().top + hitBox.getGlobalBounds().height - 5.f < map.top)
				{
					break;
				}
				position.x -= (hitBox.getGlobalBounds().left + hitBox.getGlobalBounds().width) - (map.left);
				InputManager::GetInstance().HorizontalInit();
				isDash = false;
				break;

			case Pivots::CT:
				gravity = 0.f;
				position.y += (map.top + map.height) - (hitBox.getGlobalBounds().top);
				InputManager::GetInstance().HorizontalInit();
				break;

			case Pivots::CB:
				position.y -= (hitBox.getGlobalBounds().top + hitBox.getGlobalBounds().height) - (map.top);
				gravity = 0.f;
				jumpTime = 0.f;
				isFalling = false;
				canJump = true;
				canDash = true;
				InputManager::GetInstance().HorizontalInit();
				break;

			defalut:
				break;
			}
		}
	}
}

void Player::SetXpos()
{
	position.x = positionTemp.x;
}

const RectangleShape Player::GetAttackBox()
{
	return attackBox;
}

void Player::SetHP()
{
	if (collisionTime < 0.f)
	{
		health--;
		collisionTime = 1.f;
	}
}

const RectangleShape Player::GetHitBox()
{
	return hitBox;
}

bool Player::GetIsAttackBox()
{
	return hitAttack;
}

void Player::SetIsAttackBox(bool is)
{
	hitAttack = is;
}

MAP_TYPE Player::GetCurrentMap()
{
	return currMap;
}

void Player::SetCurrentMap(MAP_TYPE type)
{
	currMap = type;
}

bool Player::UpdateCollision(const std::list<Coin*> coins)
{
	FloatRect bounds = sprite.getGlobalBounds();
	bool isCollided = false;
	for (auto coin : coins)
	{
		if (bounds.intersects(coin->GetGlobalBounds()))
		{
			coin += coin->PickUp();
		}
		isCollided = true;
	}
	return false;
}

void Player::Interaction_Stable(Stable* otherObj)
{
	// 플레이어-벤치 상호작용
	if (otherObj->CompareTag(TAG::BENCH))
	{
		animation.Play("Sit");
		(otherObj)->SetInteractable(true);
		(otherObj)->Interaction(*this);
	}
	// 플레이어-엘레베이터 상호작용
	else if (otherObj->CompareTag(TAG::ELEVATOR))
	{
		if (!(otherObj)->IsInteractable())
		{
			(otherObj)->SetInteractable(true);
		}
		else if ((otherObj)->IsInteractable())
			(otherObj)->Interaction(*this);
	}
	else
		return;
}

void Player::Interaction_Portal(Portal* portal)
{
	if ((portal)->IsInteractable())
		(portal)->Interaction(*this);
}

AnimationController& Player::GetPlayerAnimController()
{
	return animation;
}

float Player::SlowDT(float dt)
{
	if (slowTick < 60)
	{
		dt /= 60;
		++slowTick;
	}

	return dt;
}