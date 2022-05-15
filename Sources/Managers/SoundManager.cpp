#include "SoundManager.hpp"

SoundManager::~SoundManager() noexcept
{
}

void SoundManager::Init()
{
	// AddSound�� �ʿ��� ����� ���
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

	AddSound("Resources/AudioClip/focus_health_charging.wav", L"charging");
	AddSound("Resources/AudioClip/focus_health_heal.wav", L"heal");
	AddSound("Resources/AudioClip/sword_3.wav", L"sword");
	AddSound("Resources/AudioClip/enemy_damage.wav", L"enemy_damage");

	AddSound("Resources/AudioClip/geo_small_collect_1.wav", L"coin");

	// lift
	AddSound("Resources/AudioClip/lift_activate.wav", L"Lift_Active");
	AddSound("Resources/AudioClip/lift_arrive.wav", L"Lift_Arrive");
	AddSound("Resources/AudioClip/lift_moving_loop.wav", L"Lift_Moving");

	// false knight
	AddSound("Resources/AudioClip/FalseKnight/false_knight_strike_ground.wav", L"knight_strike");
	AddSound("Resources/AudioClip/FalseKnight/false_knight_land.wav", L"knight_land");
	AddSound("Resources/AudioClip/FalseKnight/false_knight_land_1st_time.wav", L"knight_land2");
	AddSound("Resources/AudioClip/FalseKnight/false_knight_jump.wav", L"knight_jump");
	AddSound("Resources/AudioClip/FalseKnight/false_knight_damage_armour.wav", L"damage_armour");
	AddSound("Resources/AudioClip/FalseKnight/false_knight_damage_armour_final.wav", L"damage_armour_final");
	AddSound("Resources/AudioClip/FalseKnight/Fknight_hit_01.wav", L"Fknight_hit");
	AddSound("Resources/AudioClip/FalseKnight/FKnight_death.wav", L"FKnight_death");
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
	// ���� ������� ���°� ������� ���
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
