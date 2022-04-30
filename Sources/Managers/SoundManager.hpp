#pragma once
#include "../include/Singleton.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
using namespace sf;

enum class Sound_Type
{
	BGM,
	EFFECT,
	COUNT,
};

class SoundManager : public Singleton<SoundManager>
{
private:
	Music music;	// bgm 
	Sound effectSound;	// effect

	std::unordered_map<SoundBuffer, Sound_Type> soundBuffers;
	std::unordered_map<std::wstring, Sound*> sounds;
public:
	SoundManager() noexcept = default;
	~SoundManager() noexcept;
public:
	int AddSound(std::wstring name);

	void PlayMusic(std::wstring name);
	void Playeffect(std::wstring name);

	std::unordered_map<SoundBuffer, Sound_Type>& getSoundBuffer();


};

