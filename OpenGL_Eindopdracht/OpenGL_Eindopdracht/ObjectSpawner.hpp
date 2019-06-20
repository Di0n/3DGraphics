#pragma once
#include <vector>
class GameObject;
class TextureManager;
class ObjectSpawner
{
public:
	enum ObjectType
	{
		Obstacle,
		Speed,
		Slow,
		Light
	};
	ObjectSpawner() {}
	ObjectSpawner(TextureManager* textureManager) : textureManager(textureManager){}

	 GameObject* spawnRandomObstacle(float spawnPos, const ObjectType& type);
private:
	TextureManager* textureManager;
	const float TARGET_X = -20.0f;
	const float TARGET_Y = -0.5f;
	const float SPAWN_POINT_X = 90;
	const float SPAWN_POINT_Y = -0.5f;
	const float MIN_Z = 1;
	const float MAX_Z = 6;
};