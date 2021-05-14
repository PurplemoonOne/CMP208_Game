#pragma once
#include "Vendor/audio_3d.h"
class Audio3D;

enum class sfxid
{
	null = -1,
	coin_sfx,
	portal_sfx,
	button_click_a,
	button_click_b
};

enum class MusicID
{
	null = -1,
	MENU,
	LEVEL
};

struct SFX
{
	std::string file_path;
	Int32 index = -1;
};

class Audio
{
protected:

	Audio(gef::Platform& platform);

public:

	static Audio* Create(gef::Platform& platform);

	//@brief Load all sound effects off disk.
	void InitialiseSoundEffects(gef::Platform* platform);
	//@brief Load all music off disk
	void InitialiseMusic(gef::Platform* platform);

	// @brief Update 3D audio.
	void Update();

	// @brief Play music
	void PlayMusic(MusicID id);

	// @brief Check if music is playing with respect to the id.
	inline const bool IsMusicPlaying(MusicID id) { return (active_music == id); }

	// @brief load a sound effect from disk
	void LoadSFX(sfxid id);
	// @brief play a sound effect
	// @param[in] Takes an id to the sfx
	// @param[in] Set sound effect to loop
	void PlaySFX(sfxid id, bool looping);

	//	@brief remove a sample.
	//  @param[in] id to the sample.
	void UnloadSFXSample(sfxid id);

	// @brief Set the volume of the master audio
	// @param[in] numerical value representing volume.
	void SetMasterVolume(float masterVolume_);

	// @brief Set the volume of music
	// @param[in] numerical value representing volume.
	void SetMusicVolume(float musicVolume_);

	// @brief Set the volume of sound effect samples.
	// @param[in] numerical value representing volume.
	void SetSFXVolume(float sfxVolume_);

	inline const float& MasterVolume() { return master_volume; }
	inline const float& MusicVolume() { return music_volume; }
	inline const float& SFXVolume() { return sound_effect_volume; }

	Audio3D* GetAudio3D() const { return audio3D; }
	gef::AudioManager* AudioManager() const { return audio_manager; }
	AudioListener& GetListener() const {return audio3D->listener(); }

private:
	gef::Platform& platform_;

	Audio3D* audio3D;
	gef::AudioManager* audio_manager;

	float master_volume;
	float music_volume;
	float sound_effect_volume;

	MusicID active_music;

	std::map<sfxid, SFX> sound_effects;
	std::map<MusicID, std::string> music;
};
