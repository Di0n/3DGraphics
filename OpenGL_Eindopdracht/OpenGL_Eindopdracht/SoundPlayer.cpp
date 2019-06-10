#include "SoundPlayer.hpp"

#include <iostream>
#include <random>

#include "Util.hpp"

using std::string;
using namespace irrklang;

SoundPlayer::SoundPlayer()
{
	soundLocation = Util::getExePath() + DEFAULT_LOCATION;
	engine = irrklang::createIrrKlangDevice();
	//TODO Set engine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
	if (!engine)
		std::cout << "Failed to create irrklang device\n";
	else
		engine->setSoundVolume(1.0f);
}
SoundPlayer::~SoundPlayer()
{
	engine->drop();
}

void SoundPlayer::cleanupSound(ISoundSource* source)
{
	if (source)
	{
		engine->removeSoundSource(source);
		//sound->stop();
		//sound->drop();
		//sound = NULL;
	}
}

void SoundPlayer::addSound(const std::string& file, const SoundID& id, bool preload)
{
	std::string loc = soundLocation + file;
	auto source = engine->addSoundSourceFromFile(loc.c_str(), irrklang::ESM_AUTO_DETECT, preload);
	//ISound* sound = engine->play2D(loc.c_str(), loop, true, false);
	sounds.insert(std::make_pair(id, source));
}
[[deprecated]]
void SoundPlayer::addSound3D(const std::string& file, const SoundID& id, bool loop, const Vec3f& pos)
{
	std::string loc = soundLocation + file;
	//ISound* sound = engine->play3D(loc.c_str(), vec3df(pos.x, pos.y, pos.z), loop, true, false);
	auto source = engine->addSoundSourceFromFile(loc.c_str(), irrklang::ESM_AUTO_DETECT, true);
	sounds.insert(std::make_pair(id, source));
}
[[deprecated]]
ISound* SoundPlayer::getSound(const SoundID& id)
{
	if (sounds.find(id) == sounds.end())
		return nullptr; // Sound not found
	return nullptr;//sounds[id];
}

void SoundPlayer::deleteSound(const SoundID& id)
{
	if (sounds.find(id) != sounds.end())
	{
		//ISound* sound = sounds[id];
		auto source = sounds[id];
		cleanupSound(source);
		sounds.erase(id);
	}
}

void SoundPlayer::setListenerPosition(const Vec3f& pos, const Vec3f& heading)
{
	engine->setListenerPosition(vec3df(pos.x, pos.y, pos.z), vec3df(heading.x, heading.y, heading.z));
}

void SoundPlayer::playSound(const SoundID& sound, bool looped)
{
	auto source = getSoundSource(sound);
	if (source != nullptr)
	{
		engine->play2D(source);
	}
}

ISound* SoundPlayer::playSound3D(const SoundID& sound, const Vec3f& pos, bool looped)
{
	auto source = getSoundSource(sound);
	if (source != nullptr)
	{
		return engine->play3D(source, vec3df(pos.x, pos.y, pos.z), looped, false, true, false);
	}
	return nullptr;
}

irrklang::ISoundSource* SoundPlayer::getSoundSource(SoundID sound)
{
	if (sounds.find(sound) == sounds.end())
		return nullptr; // Sound not found
	return sounds[sound];//sounds[id];
}


SoundID SoundPlayer::getAvailableSoundID()
{
	size_t length = 16;
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	//thread_local static std::mt19937 rg{ std::random_device{}() };
	//thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[Util::getRandomNumber<std::string::size_type>(0, sizeof(chrs) - 2)];

	return s;
}