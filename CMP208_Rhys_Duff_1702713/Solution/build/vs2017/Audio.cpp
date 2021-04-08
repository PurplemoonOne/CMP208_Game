#include "pch.h"
#include "Audio.h"

Audio::Audio(gef::Platform& platform) : platform_(platform)
{
	audio_manager = gef::AudioManager::Create();

	audio3D = new Audio3D(audio_manager);

	SetMasterVolume(100.0f);
	SetMusicVolume(100.0f);
	sound_effect_volume = 100.0f;

	InitialiseSoundEffects();
	InitialiseMusic();
}

Audio* Audio::Create(gef::Platform& platform)
{
	return new Audio(platform);
}

void Audio::InitialiseSoundEffects()
{



}

void Audio::InitialiseMusic()
{

}

void Audio::Update()
{
	if (audio3D)
	{
		audio3D->Update();
	}
}

void Audio::PlayMusic(MusicID id)
{
	audio_manager->StopMusic();

	if (id == MusicID::null)
	{
		return;
	}

	audio_manager->LoadMusic(music.at(id).c_str(), platform_);
	audio_manager->PlayMusic();

	active_music = id;
}

void Audio::LoadSFX(sfxid id)
{
	audio_manager->LoadSample(sound_effects.at(id).filePath.c_str(), platform_);
}

void Audio::PlaySFX(sfxid id, bool looping)
{
	if (id == sfxid::null)
	{
		return;
	}

	audio_manager->PlaySample(sound_effects.at(id).index, looping);
}

void Audio::UnloadSFXSample(sfxid id)
{
	audio_manager->UnloadSample(sound_effects.at(id).index);
}

void Audio::SetMasterVolume(float masterVolume_)
{
	master_volume = masterVolume_;

	audio_manager->SetMasterVolume(master_volume);
}

void Audio::SetMusicVolume(float musicVolume_)
{
	music_volume = musicVolume_;

	gef::VolumeInfo info;

	info.volume = music_volume;
	info.pan = 0.0f;

	audio_manager->SetMusicVolumeInfo(info);
}

void Audio::SetSFXVolume(float sfxVolume_)
{
	sound_effect_volume = sfxVolume_;

	gef::VolumeInfo info;

	info.volume = sound_effect_volume;

	for (auto& effect : sound_effects)
	{
		Int32 index = sound_effects.at(effect.first).index;

		audio_manager->SetSampleVoiceVolumeInfo(index, info);
	}
}
