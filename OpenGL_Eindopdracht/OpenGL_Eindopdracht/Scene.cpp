#include "Scene.hpp"
#include <GL\freeglut.h>
#include "TextureManager.hpp"
#include "TextureResource.hpp"
#include "Camera.hpp"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "CameraComponent.hpp"
#include "FloorComponent.hpp"
#include "SlabComponent.hpp"
#include "WallComponent.h"

void Scene::setup()
{
	// PLAYER
	GameObject* player = new GameObject();
	player->addComponent(new PlayerComponent());
	//player->addComponent(new CubeComponent(0.3f));
	player->addComponent(new CameraComponent(camera));
	player->position = Vec3f(-6, 0, 4);
	objects->push_back(player);

	setupFloor();
	setupWalls();
	setupCeiling();
}

void Scene::setupWalls()
{
	// Walls
	GLuint textureID = textureManager->getTexture(TEXTURE_WALL);
	
}

void Scene::setupFloor()
{
	// FLOOR
	GLuint textureID = textureManager->getTexture(TEXTURE_FLOOR);
	
	const float size = 1;
	const float rows = 8;
	const float columns = 10;

	for (float i = 0 + (size * 2); i < (rows + (size * 2)); i += (size * 2))
	{
		for (float j = -columns; j < (columns + (size * 2)); j += (size * 2))
		{
			GameObject* floor = new GameObject();
			floor->addComponent(new SlabComponent(size, textureID));
			floor->position = Vec3f(j, 0, i);
			floor->rotation = Vec3f(90,0,0);

			objects->push_back(floor);
		}
	}
}

void Scene::setupCeiling()
{

}