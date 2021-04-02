#ifndef _AUDIO_3D_H
#define _AUDIO_3D_H

#include <audio/audio_manager.h>
#include "audio_listener.h"
#include "audio_emitter.h"
#include <vector>

class Audio3D
{
public:
	Audio3D(gef::AudioManager* audio_manager);

	void Update();

	void AddEmitter(const AudioEmitter& emitter);

	inline AudioListener& listener() { return listener_; }

	inline void SetMasterVolume(float value);
	inline void SetMusicVolume(float value);
	inline void SetSFXVolume(float value, int id); 

private:
	gef::AudioManager* audio_manager_;
	AudioListener listener_;

	float sfx_volume;
	float master_volume;
	float music_volume;

	std::vector<AudioEmitter> emitters_;
//	AudioEmitter emitters_[20];
};

#endif // _AUDIO_3D_H