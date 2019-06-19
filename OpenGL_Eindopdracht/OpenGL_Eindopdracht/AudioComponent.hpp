#pragma once
#include "Component.h"
#include "SoundPlayer.hpp"

class AudioComponent : public Component
{
public:
	AudioComponent(const SoundID& id) : soundID(id) 
	{
		soundplayer = &SoundPlayer::getInstance();
	}
	~AudioComponent();

	void playSound(bool looping);
	void stopSound();

	virtual void update(float deltaTime) override;
private:
	SoundID soundID;
	SoundPlayer* soundplayer;
	irrklang::ISound* sound;
};