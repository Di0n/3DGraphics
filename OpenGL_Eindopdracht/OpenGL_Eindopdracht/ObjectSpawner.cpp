#include "ObjectSpawner.hpp"
#include <GL\freeglut.h>
#include "GameObject.h"
#include "Util.hpp"
#include "Tags.hpp"
#include "TextureManager.hpp"
#include "TextureResource.hpp"
#include "CubeComponent.h"
#include "HitboxComponent.hpp"
#include "MoveToComponent.h"
#include "AudioComponent.hpp"
#include "MusicResources.hpp"


GameObject* ObjectSpawner::spawnRandomObstacle(float spawnPos, const ObjectType& type)
{
	GameObject* obstacle = new GameObject();
	GLuint textureID;
	std::string tag;
	switch (type)
	{
	case ObjectType::Obstacle:
	{
		tag = Tags::OBSTACLE;
		textureID = textureManager->getTexture(TEXTURE_MBOX);

		break;
	}
	case ObjectType::Speed:
		break;
	case ObjectType::Slow:
		break;
	case ObjectType::Light:
	{
		tag = Tags::EMP;
		textureID = textureManager->getTexture(TEXTURE_EMPBOX);
		auto ac = new AudioComponent(MusicResources::ELECTRICAL_SOUND);
		obstacle->addComponent(ac);
		ac->playSound(true);
		break;
	}
	default:
		break;
	}
	obstacle->tag = tag;
	float randomZ = Util::getRandomNumber<int>(MIN_Z, MAX_Z);
	randomZ = (randomZ == MIN_Z) ? randomZ + 0.5f : randomZ;
	randomZ = (randomZ == MAX_Z) ? randomZ - 0.5f : randomZ;
	float randomDivider = Util::getRandomNumber<int>(0, 100);
	randomZ += (randomDivider / 100.0f);
	obstacle->position = Vec3f(spawnPos, SPAWN_POINT_Y, randomZ);

	const float cubeSize = 0.5f;
	obstacle->addComponent(new CubeComponent(cubeSize, textureID));
	obstacle->addComponent(new HitboxComponent(cubeSize, cubeSize, cubeSize));
	MoveToComponent* m = new MoveToComponent();
	m->target = Vec3f(TARGET_X, TARGET_Y, randomZ);
	m->speed = 5;
	obstacle->rotation = Vec3f(0, 90, 0);
	obstacle->addComponent(m);

	return obstacle;
}