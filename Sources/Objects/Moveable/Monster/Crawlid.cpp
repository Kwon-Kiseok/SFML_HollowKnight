#include "Crawlid.hpp"
#include "../../Sources/Animation/rapidcsv.hpp"
//#include "../../Sources/Managers/InputManager.hpp"
#include "../../Sources/Managers/TextureManager.hpp"
#include "../../Sources/Utils/Utility.hpp"

Crawlid::Crawlid()
{
	isAlive = true;
	health = 2;
	gravity = GRAVITY;
	coin = 3;
}

Crawlid::Crawlid(int xdir)
{
	if (xdir > 0)				// 처음에 오른쪽으로 이동
	{
		xDir = 1;
	}
	else if (xdir < 0)			// 처음에 왼쪽으로 이동
	{
		xDir = -1;
	}
	health = 2;
	gravity = GRAVITY;
}

void Crawlid::Init()
{
	SetName("crawlid");
	SetTag(TAG::MONSTER);
	SetName("Crawlid");
	moveSpeed = 100.f;
	//sprite.setOrigin(60, 60);
	// Animator 초기화
	animation.SetTarget(&sprite);

	rectangleShape.setSize(Vector2f(110, 55));
	rectangleShape.setOrigin(Vector2f(55, 70));
	rectangleShape.setPosition(position);
	rectangleShape.setFillColor(Color::Transparent);
	rectangleShape.setOutlineColor(Color::Red);
	rectangleShape.setOutlineThickness(2);

	gavityShape.setSize(Vector2f(90, 65));
	gavityShape.setOrigin(Vector2f(45, 75));
	gavityShape.setPosition(position);
	gavityShape.setFillColor(Color::Transparent);
	gavityShape.setOutlineColor(Color::Blue);
	gavityShape.setOutlineThickness(2);

	sideShape.setSize(Vector2f(110, 30));
	sideShape.setOrigin(Vector2f(55, 55));
	sideShape.setPosition(position);
	sideShape.setFillColor(Color::Transparent);
	sideShape.setOutlineColor(Color::Yellow);
	sideShape.setOutlineThickness(2);

	rapidcsv::Document clips("data_tables/animations/crawlid/crawlid_animation_clips.csv");

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

	sprite.setScale(-xDir, 1);

	textureDroppedCoin = new Texture[3];
	spriteDroppedCoin = new Sprite[3];
	for (int i = 0; i < 3; i++)
	{
		textureDroppedCoin[i] = TextureManager::GetInstance().GetTexture("Resources/Sprite/UI/HUD_coin_v020004_.png");
		spriteDroppedCoin[i].setTexture(textureDroppedCoin[i]);
		spriteDroppedCoin[i].setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height + 40.f);

	}
}

void Crawlid::Update(float dt, Vector2f player)
{
	if (lodingTime > 0.f)
	{
		lodingTime -= dt;
		gravity = 0.f;
	}

	positionTemp = position;

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

	if (health <= 0)
	{
		isAlive = false;
		animation.Play("Die");
	}

	if (isAlive)
	{
		position.x += (moveSpeed * dt) * xDir;
	}
	// position
	//SetPosition(position);
	sprite.setPosition(position);
	rectangleShape.setPosition(position);
	gavityShape.setPosition(position);
	sideShape.setPosition(position);
	// animation
	animation.Update(dt);

	if (!isAlive)
	{
		for (int i = 0; i < 3; i++)
		{
			spriteDroppedCoin[i].setPosition(position);
		}
	}
}

void Crawlid::Render(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(rectangleShape);
	//window.draw(gavityShape);
	//window.draw(sideShape);

	for (int i = 0; i < 3; i++)
	{
		window.draw(spriteDroppedCoin[i]);
	}
}

void Crawlid::Release()
{
}

void Crawlid::OnGround(FloatRect map)
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

//void Crawlid::OnGround(FloatRect map)
//{
//	if (sideShape.getGlobalBounds().intersects(map))
//	{
//		xDir = -xDir;
//		sprite.scale(-1, 1);
//	}
//	if (gavityShape.getGlobalBounds().intersects(map))
//	{
//		gravity = 0.f;
//		isFalling = false;
//	}
//	else
//	{
//		xDir = -xDir;
//		sprite.scale(-1, 1);
//	}
//}

bool Crawlid::UpdateCollision()
{
	return false;
}

bool Crawlid::OnHitted(Time timeHit)
{
	health--;
	if (health == 0)
	{
		PlayerDataManager::GetInstance().AddCoin(3);
	}
	return false;
}
