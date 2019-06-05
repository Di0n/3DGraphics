#include "Level.hpp"
#include <GL\freeglut.h>
#include "GameObject.h"
#include "PlayerComponent.h"
#include "CameraComponent.hpp"
#include "CubeComponent.h"
#include "FloorComponent.hpp"
#include "WallComponent.h"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "TextureResource.hpp"

void Level::setupWalls()
{
	// BACK WALLS
	GLuint textureID;
	textureManager->getTexture(TEXTURE_WALL, &textureID);
	GameObject* wallObject = new GameObject();
	wallObject->addComponent(new WallComponent(1, textureID));
	wallObject->position = Vec3f(0, 0, 0);
	objects->push_back(wallObject);
}

void Level::setupFloor()
{
	// FLOOR
	GLuint textureID;
	textureManager->getTexture(TEXTURE_FLOOR, &textureID);
	
	int x = 0;
	const float size = 1;
	for (int i = 0 + (size*2); i < (5 + (size*2)); i+= (size*2))
	{
		for (int j = -10; j < (10+(size*2)); j+=(size*2))
		{
			//if (x++ == 2) goto LOL;
			GameObject* floor = new GameObject();
			floor->addComponent(new FloorComponent(size, textureID));
			floor->position = Vec3f((float)j, 0, (float)i);

			objects->push_back(floor);
		}
	}
//LOL:;
}
void Level::setup()
{
	// PLAYER
	GameObject* player = new GameObject();
	player->addComponent(new PlayerComponent());
	player->addComponent(new CameraComponent(camera));

	player->position = Vec3f(0, 0, 0);

	// TEST
	GameObject* o = new GameObject();
	o->addComponent(new CubeComponent(0.5));
	o->position = Vec3f(0, 4, 0);
	
	setupWalls();
	setupFloor();
	GLuint textureID;
	// TABLE
	//textureManager->getTexture(TEXTURE_TABLE, &textureID);
	//GameObject* table = new GameObject();


	objects->push_back(o);
	objects->push_back(player);
}