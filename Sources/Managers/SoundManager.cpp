#include "SoundManager.hpp"

SoundManager::~SoundManager() noexcept
{
}

void SoundManager::Init()
{
	// AddSound로 필요한 사운드들 등록

}

void SoundManager::AddSound(std::string path, std::wstring id)
{
	SoundBuffer* buffer = new SoundBuffer;
	Sound* sound = new Sound;

	buffer->loadFromFile(path);
	sound->setBuffer(*buffer);

	soundBuffers.insert(make_pair(id, buffer));
	effectSounds.insert(make_pair(id, sound));
}

void SoundManager::PlayMusic(std::string path)
{
	// 현재 배경음악 상태가 재생중인 경우
	if (music.getStatus() == Music::Status::Playing)
	{
		music.stop();
	}

	if (!music.openFromFile(path))
	{
		return;
	}
	music.play();
	music.setLoop(true);
}

void SoundManager::PlaySound(std::wstring id)
{
	auto it = effectSounds.find(id);
	it->second->play();
}
