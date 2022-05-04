#include "Player.hpp"
#include "../Animation/rapidcsv.hpp"
#include "../Managers/InputManager.hpp"

Player::Player()
	: isMove(true), isWay(true), isJump(true), isBottom(false), speed(200.f)
{
}

void Player::Init()
{
	position.x = 1920.f / 2;
	// position.y = 1080.f / 2;
	position.y = 500.f;
	sprite.setPosition(position);

	sprite.setOrigin(31, 0);
	// Animator �ʱ�ȭ
	animation.SetTarget(&sprite);

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
		//sprite.setOrigin(orgX, orgY);
		// Animator �ʱ�ȭ		// AnimationController Update���� ������ �� ����
		//animation.SetTarget(&sprite);

		animation.AddClip(clip);
	}

	animation.Play("Idle");
}

void Player::UpdateInput()
{
	// �¿� �Է½� �̹��� ���� ��ȭ
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right))
	{
		if (isWay)
		{
			sprite.scale(-1, 1);
			isWay = !isWay;
		}
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Left))
	{
		if (!isWay)
		{
			sprite.scale(-1, 1);
			isWay = !isWay;
		}
	}
	// �¿� �̵� �̹���
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyDown(Keyboard::Left))
	{
		if (isBottom)
		{
			animation.Play("StartMove");
			animation.PlayQueue("Move");
		}
	}
	// �¿� �̵� -> ���� �̹���
	if ((InputManager::GetInstance().GetKeyUp(Keyboard::Right) ||
		InputManager::GetInstance().GetKeyUp(Keyboard::Left)))
	{
		if (isBottom)
		{
			animation.Play("RunToIdle");
			animation.PlayQueue("Idle");
		}
	}

	if (InputManager::GetInstance().GetKeyDown(Keyboard::Z))
	{
		animation.Play("Jump");
		animation.PlayQueue("Jumping");
		isJump = true;
		if (isBottom)
		{
			//animation.PlayQueue("Idle");	// ���� �̹�����
		}
	}
	// ���� �ִϸ��̼� or ���� �̹��� �����ϴ� ��????
	if (InputManager::GetInstance().GetKeyDown(Keyboard::X))
	{
		animation.Play("Slash");
		animation.PlayQueue("Idle");	// ���� �̹�����
	}
}

void Player::Update(float dt, FloatRect tile)
{
	UpdateInput();

	Vector2f positionTemp = position;
	
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Right) ||
		InputManager::GetInstance().GetKey(Keyboard::Right))
	{
		position.x += dt * speed;
	}
	if (InputManager::GetInstance().GetKeyDown(Keyboard::Left) ||
		InputManager::GetInstance().GetKey(Keyboard::Left))
	{
		position.x -= dt * speed;
	}

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
	
	sprite.setPosition(position);

	animation.Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

FloatRect Player::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}
