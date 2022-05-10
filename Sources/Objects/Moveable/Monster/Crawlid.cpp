#include "Crawlid.hpp"
#include "../../Sources/Animation/rapidcsv.hpp"
#include "../../Sources/Managers/InputManager.hpp"

Crawlid::Crawlid()
	:gravity(GRAVITY)
{
}

Crawlid::Crawlid(int xdir)
	: gravity(GRAVITY)
{
	if (xdir > 0)				// ó���� ���������� �̵�
	{
		xDir = 1;
	}
	else if (xdir < 0)			// ó���� �������� �̵�
	{
		xDir = -1;
	}
}

void Crawlid::Init()
{
	SetTag(TAG::MONSTER);
	moveSpeed = 100.f;
	//sprite.setOrigin(60, 60);
	// Animator �ʱ�ȭ
	animation.SetTarget(&sprite);

	rectangleShape.setSize(Vector2f(110, 55));
	rectangleShape.setOrigin(Vector2f(55, 70));
	rectangleShape.setPosition(position);
	rectangleShape.setFillColor(Color::Transparent);
	rectangleShape.setOutlineColor(Color::Red);
	rectangleShape.setOutlineThickness(2);

	gavityShape.setSize(Vector2f(60, 65));
	gavityShape.setOrigin(Vector2f(30, 75));
	gavityShape.setPosition(position);
	gavityShape.setFillColor(Color::Transparent);
	gavityShape.setOutlineColor(Color::Blue);
	gavityShape.setOutlineThickness(2);

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
}

void Crawlid::Update(float dt)
{
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

	position.x += (moveSpeed * dt) * xDir;
	// position
	SetPosition(position);
	rectangleShape.setPosition(position);
	gavityShape.setPosition(position);
	// animation
	animation.Update(dt);
}

void Crawlid::Render(RenderWindow& window)
{
	window.draw(sprite);
	window.draw(rectangleShape);
	window.draw(gavityShape);
}

void Crawlid::Release()
{
}

void Crawlid::OnGround(FloatRect map)
{
	if (rectangleShape.getGlobalBounds().intersects(map))
	{
		std::cout << "���� �浹" << std::endl;
		xDir = -xDir;
		sprite.scale(-1, 1);
	}
	if (gavityShape.getGlobalBounds().intersects(map))
	{
		gravity = 0.f;
		isFalling = false;
	}
}