#include "EffectManager.hpp"
#include "rapidcsv.hpp"
/************************************************
* 
*************************************************/
void EffectManager::Init()
{
	position.x = 512.f;
	position.y = 512.f;
	effectSprite.setPosition(position);
	//sprite.setOrigin(60, 60);
	// Animator √ ±‚»≠
	effect.SetTarget(&effectSprite);

	rapidcsv::Document clips("data_tables/animations/effect/effect_animation_clips.csv");

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
		effect.AddClip(clip);
	}

	effect.Play("Slash");
}

void EffectManager::Update(Vector2f playerPosition)
{
	//position = playerPosition;
	effectSprite.setPosition(playerPosition);
}

void EffectManager::Draw(RenderWindow& window)
{
	window.draw(effectSprite);
}

void EffectManager::SetDraw(std::string string)
{
	effect.Play(string);
}
