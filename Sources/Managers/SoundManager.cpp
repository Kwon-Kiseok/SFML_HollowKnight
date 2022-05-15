#include "SoundManager.hpp"

SoundManager::~SoundManager() noexcept
{
}

void SoundManager::Init()
{
	// AddSound로 필요한 사운드들 등록
	AddSound("Resources/AudioClip/ui_button_confirm.wav", L"select");
	AddSound("Resources/AudioClip/ui_change_selection.wav", L"changeMenu");
	AddSound("Resources/AudioClip/bench_rest.wav", L"bench");
// ////////////////////////////////////////////////////////////////////////

	AddSound("Resources/AudioClip/Hero/hero_run_footsteps_stone.wav", L"walk");
	AddSound("Resources/AudioClip/Hero/hero_jump.wav", L"jump");
	AddSound("Resources/AudioClip/Hero/hero_dash.wav", L"dash");
	AddSound("Resources/AudioClip/Hero/hero_parry.wav", L"parry");
	AddSound("Resources/AudioClip/Hero/hero_land_hard.wav", L"land");
	AddSound("Resources/AudioClip/Hero/hero_damage.wav", L"damage");


	AddSound("Resources/AudioClip/sword_3.wav", L"sword");
	AddSound("Resources/AudioClip/enemy_damage.wav", L"enemy_damage");

	AddSound("Resources/AudioClip/geo_small_collect_1.wav", L"coin");

	// lift
	AddSound("Resources/AudioClip/lift_activate.wav", L"Lift_Active");
	AddSound("Resources/AudioClip/lift_arrive.wav", L"Lift_Arrive");
	AddSound("Resources/AudioClip/lift_moving_loop.wav", L"Lift_Moving");

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

void SoundManager::StopMusic()
{
	music.stop();
}

void SoundManager::PlaySound(std::wstring id)
{
	auto it = effectSounds.find(id);
	it->second->play();
}

Sound& SoundManager::GetSoundbyID(std::wstring id)
{
	auto it = effectSounds.find(id);
	return *(it->second);
}

void SoundManager::Release()
{
	for (auto it = effectSounds.begin(); it != effectSounds.end(); ++it)
	{
		delete it->second;
	}
	effectSounds.clear();

	for (auto it = soundBuffers.begin(); it != soundBuffers.end(); ++it)
	{
		delete it->second;
	}
	soundBuffers.clear();
}
