#include "SoundManager.hpp"

SoundManager::~SoundManager() noexcept
{
}

int SoundManager::AddSound(std::wstring name)
{
	auto iter = sounds.find(name);
	if (iter != sounds.end())
	{
		return -1;
	}

	// ÀÛ¼ºÁß
}

void SoundManager::PlayMusic(std::wstring name)
{
}

void SoundManager::Playeffect(std::wstring name)
{
}

std::unordered_map<SoundBuffer, Sound_Type>& SoundManager::getSoundBuffer()
{
	return soundBuffers;
}
