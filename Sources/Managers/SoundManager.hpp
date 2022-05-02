#pragma once
#include "../include/Singleton.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
using namespace sf;

class SoundManager : public Singleton<SoundManager>
{
private:
	std::unordered_map<std::wstring, SoundBuffer*> soundBuffers;
	std::unordered_map<std::wstring, Sound*> effectSounds;
	Music music;
public:
	SoundManager() noexcept = default;
	~SoundManager() noexcept;
public:

	void Init();
	void AddSound(std::string path, std::wstring id);
	void PlayMusic(std::string path);
	void PlaySound(std::wstring id);
};

// 사용중인 사운드, 사용중이지 않은 사운드 나눠놓고 관리하는 방법도 있음