#include "Vengefly.hpp"
#include "../../Sources/Animation/rapidcsv.hpp"
//#include "../../Sources/Managers/InputManager.hpp"
#include "../../Sources/Managers/TextureManager.hpp"
#include "../../Sources/Utils/Utility.hpp"

Vengefly::Vengefly()
{
	isAlive = true;
	health = 2;
	gravity = GRAVITY;
	coin = 3;
}

Vengefly::Vengefly(int xdir)
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
	coin = 3;
}

void Vengefly::Init()
{
	SetName("vengefly");
	SetTag(TAG::MONSTER);
	SetName("Vengefly");
	moveSpeed = 100.f;
	SetLayer(5);
	animation.SetTarget(&sprite);

	rectangleShape.setSize(Vector2f(110, 55));
	rectangleShape.setOrigin(Vector2f(55, 70));
	rectangleShape.setPosition(position);
	rectangleShape.setFillColor(Color::Transparent);
	rectangleShape.setOutlineColor(Color::Red);
	rectangleShape.setOutlineThickness(2);

	detectShape.setSize(Vector2f(400, 400));
	detectShape.setOrigin(Vector2f(200, 250));
	detectShape.setPosition(position);
	detectShape.setFillColor(Color::Transparent);
	detectShape.setOutlineColor(Color::Blue);
	detectShape.setOutlineThickness(2);

	rapidcsv::Document clips("data_tables/animations/vengefly/vengefly_animation_clips.csv");

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

	sprite.setScale(-xDir, 1);
}

void Vengefly::Update(float dt, Vector2f playerPos)
{
	if (health <= 0)
	{
		isAlive = false;
		animation.Play("Die");
	}

	if (isAlive)
	{
		if (isDetect)
		{
			if (once)
			{
				animation.Play("Detect");
				animation.PlayQueue("Chase");
				once = false;
			}
			Vector2f positionTemp = position;

			float x = playerPos.x - position.x;
			float y = playerPos.y - position.y;
			Vector2f dir(x, y);

			dir = Utility::Normalize(dir);

			position += dir * moveSpeed * dt;	// v = dt			
		}
		if (playerPos.x < position.x)
		{
			sprite.setScale(1, 1);
		}
		else
		{
			sprite.setScale(-1, 1);
		}
	}
	else
	{
		if (isFalling)
		{
			gravity += GRAVITY * dt;
			if (gravity > 500.f)
			{
				gravity = 500.f;
			}
			position.y += gravity * dt;
		}
		isFalling = true;
	}
	// position
	SetPosition(position);
	rectangleShape.setPosition(position);
	detectShape.setPosition(position);
	// animation
	animation.Update(dt);
}

void Vengefly::Render(RenderWindow& window)
{
	window.draw(sprite);

	if (MapManager::GetInstance().GetIsDebugMode())
	{
		window.draw(rectangleShape);
		window.draw(detectShape);
	}
}

void Vengefly::Release()
{
}

void Vengefly::OnGround(FloatRect map)
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

bool Vengefly::UpdateCollision()
{
	return false;
}

bool Vengefly::OnHitted(Time timeHit)
{
	health--;

	if (health == 0)
	{
		PlayerDataManager::GetInstance().AddCoin(3);
	}
	return false;
}

RectangleShape Vengefly::GetDetectShape()
{
	return detectShape;
}

void Vengefly::SetIsDetect(bool is)
{
	isDetect = is;
}
