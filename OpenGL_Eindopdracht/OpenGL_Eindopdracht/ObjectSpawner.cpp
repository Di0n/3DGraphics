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


GameObject* ObjectSpawner::spawnRandomObstacle(float spawnPos, const ObjectType& type)
{
	GameObject* obstacle = new GameObject();

	switch (type)
	{
	case ObjectType::Obstacle:
		
		break;
	case ObjectType::Speed:
		break;
	case ObjectType::Slow:
		break;
	case ObjectType::Light:
		
		break;
	default:
		break;
	}
	obstacle->tag = Tags::OBSTACLE;
	float randomZ = Util::getRandomNumber<int>(MIN_Z, MAX_Z);
	randomZ = (randomZ == MIN_Z) ? randomZ + 0.5f : randomZ;
	randomZ = (randomZ == MAX_Z) ? randomZ - 0.5f : randomZ;
	float randomDivider = Util::getRandomNumber<int>(0, 100);
	randomZ += (randomDivider / 100.0f);
	obstacle->position = Vec3f(spawnPos, SPAWN_POINT_Y, randomZ);

	const float cubeSize = 0.5f;
	GLuint texture = textureManager->getTexture(TEXTURE_BOX);
	obstacle->addComponent(new CubeComponent(cubeSize, texture));
	obstacle->addComponent(new HitboxComponent(cubeSize, cubeSize, cubeSize));
	MoveToComponent* m = new MoveToComponent();
	m->target = Vec3f(TARGET_X, TARGET_Y, randomZ);
	m->speed = 5;
	obstacle->rotation = Vec3f(0, 90, 0);
	obstacle->addComponent(m);

	return obstacle;
}