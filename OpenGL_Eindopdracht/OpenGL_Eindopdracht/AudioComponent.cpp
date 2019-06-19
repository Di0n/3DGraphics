#include "AudioComponent.hpp"

#include <Gl\freeglut.h>
#include "GameObject.h"
AudioComponent::~AudioComponent()
{
	if (sound)
	{
		stopSound();
	}
}
void AudioComponent::update(float dt)
{
	if (!sound) return;

	const Vec3f* pos = &gameObject->position;
	sound->setPosition(irrklang::vec3df(pos->x, pos->y, pos->z));
}

void AudioComponent::playSound(bool looping)
{
	//if (sound && !sound->isFinished())
	//{
	//	//
	//}
	if (!sound || (sound && sound->isFinished()))
	{
		stopSound();
		sound = soundplayer->playSound3D(soundID, gameObject->position, looping);
	}
}

void AudioComponent::stopSound()
{
	if (sound)
	{
		sound->setIsPaused(true);
		sound->drop();
		sound = nullptr;
	}
}