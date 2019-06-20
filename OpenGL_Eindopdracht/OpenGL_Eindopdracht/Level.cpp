#include "Level.hpp"
#include <GL\freeglut.h>
#include "GameObject.h"
#include "PlayerComponent.h"
#include "CameraComponent.hpp"
#include "CubeComponent.h"
#include "FloorComponent.hpp"
#include "WallComponent.h"
#include "GravityComponent.hpp"
#include "SphereComponent.hpp"
#include "Camera.hpp"
#include "TextureManager.hpp"
#include "TextureResource.hpp"

void Level::setupWalls()
{
	// BACK WALLS
	GLuint textureID = textureManager->getTexture(TEXTURE_WALL);
	GameObject* wallObject = new GameObject();
	wallObject->addComponent(new WallComponent(1, textureID));
	wallObject->position = Vec3f(0, 0, 0);
	objects->push_back(wallObject);
}

void Level::setupFloor()
{
	// FLOOR
	GLuint textureID = textureManager->getTexture(TEXTURE_FLOOR);
	
	const float size = 1;
	const float rows = 8;
	const float colums = 10;
	for (float i = 0 + (size*2); i < (rows + (size*2)); i+= (size*2))
	{
		for (float j = -colums; j < (colums+(size*2)); j+=(size*2))
		{
			GameObject* floor = new GameObject();
			floor->addComponent(new FloorComponent(size, textureID));
			floor->position = Vec3f(j, 0, i);

			objects->push_back(floor);
		}
	}
}
void Level::setup()
{
	// PLAYER
	GameObject* player = new GameObject();
	player->addComponent(new PlayerComponent());
	//player->addComponent(new CubeComponent(0.3f));
	player->addComponent(new CameraComponent(camera));

	player->position = Vec3f(-6 ,0, 4);

	// TEST
	/*GameObject* o = new GameObject();
	o->tag = "CUBE";
	o->addComponent(new CubeComponent(0.5));
	o->position = Vec3f(0, 4, 4);*/
	
	setupWalls();
	setupFloor();

	GLuint textureID = textureManager->getTexture(TEXTURE_CASTLE);
	GameObject* wallObject = new GameObject();
	wallObject->addComponent(new WallComponent(20, textureID));
	wallObject->position = Vec3f(10, 8, 5);
	wallObject->rotation = Vec3f(0, 90, 0);
	objects->push_back(wallObject);

	//textureManager->getTexture(TEXTURE_BALL, &textureID);
	//GameObject* sphere = new GameObject();
	//sphere->addComponent(new SphereComponent(1.0f, textureID));
	//sphere->position = Vec3f(-4, 0, 4);
	//objects->push_back(sphere);

	textureID = textureManager->getTexture(TEXTURE_MBOX);
	GameObject* box = new GameObject();
	box->addComponent(new CubeComponent(0.8f, textureID));
	box->position = Vec3f(-4, 0, 4);
	objects->push_back(box);
	// TABLE
	//textureManager->getTexture(TEXTURE_TABLE, &textureID);
	//GameObject* table = new GameObject();


	//objects->push_back(o);
	objects->push_back(player);
}