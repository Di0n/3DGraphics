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
#include "CubeComponent.h"
#include "SphereComponent.hpp"
#include "HitboxComponent.hpp"
#include "AudioComponent.hpp"
#include "Tags.hpp"

void Scene::setup()
{
	// CAMERA
	camera->rotY = 120;
	// PLAYER
	GameObject* player = new GameObject();
	player->tag = Tags::PLAYER;
	player->addComponent(new PlayerComponent());
	//player->addComponent(new CubeComponent(0.3f,5));
	player->addComponent(new CameraComponent(camera));
	const float playerHitbox = 0.3f;
	player->addComponent(new HitboxComponent(playerHitbox, playerHitbox, playerHitbox));
	player->addComponent(new AudioComponent(Tags::DEATH_SOUND));
	player->position = Vec3f(-8, 0, 4);
	//player->rotation = Vec3f(0, 0, 240);
	objects->push_back(player);

	setupFloor();
	setupWalls();
	setupCeiling();
}

void Scene::setupWalls()
{
	// Walls
	GLuint textureID = textureManager->getTexture(TEXTURE_WALL_1);

	const float size = 1;
	const float walls = 90;
	const float startingPosWalls = -10;
	const float area = size * 2;

	// SIDE WALLS 1
	for (float i = startingPosWalls; i < (walls + area); i+= area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(size, textureID));
		wall->position = Vec3f(i,0,0);
		objects->push_back(wall);
	}
	// Side walls 1 top
	for (float i = startingPosWalls; i < (walls + area); i += area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(size, textureID));
		wall->position = Vec3f(i, area, 0);
		objects->push_back(wall);
	}
	// BACK WALLS
	const float startingPosBackWalls = 2;
	const float backWalls = 5;

	for (float i = startingPosBackWalls; i < (backWalls + area); i += area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(1, textureID));
		wall->position = Vec3f(-10, 0, i);
		wall->rotation = Vec3f(0,-90,0);
		objects->push_back(wall);
	}

	for (float i = startingPosBackWalls; i < (backWalls + area); i += area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(1, textureID));
		wall->position = Vec3f(-10, area, i);
		wall->rotation = Vec3f(0, -90, 0);
		objects->push_back(wall);
	}

	// SIDE WALLS 2
	for (float i = startingPosWalls ; i < (walls + area); i += area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(1, textureID));
		wall->position = Vec3f(i, 0, 6);
		objects->push_back(wall);
	}
	// Side walls 2 top
	for (float i = startingPosWalls; i < (walls + area); i += area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(1, textureID));
		wall->position = Vec3f(i, area, 6);
		objects->push_back(wall);
	}

	GLuint finishTexture = textureManager->getTexture(TEXTURE_FINISH);
	const float startingPosFinishWalls = 2;
	const float finishWalls = 5;
	for (float i = startingPosFinishWalls; i < (finishWalls + area); i += area)
	{

		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(1, finishTexture));
		wall->position = Vec3f(90, 0, i);
		wall->rotation = Vec3f(0, 90, 0);
		objects->push_back(wall);
		
	}

	for (float i = startingPosFinishWalls; i < (finishWalls + area); i += area)
	{
		GameObject* wall = new GameObject();
		wall->tag = Tags::WALL;
		wall->addComponent(new SlabComponent(1, textureID));
		wall->position = Vec3f(90, area, i);
		wall->rotation = Vec3f(0, 90, 0);
		objects->push_back(wall);
	}
	/*GameObject* w = new GameObject();

	w->addComponent(new CubeComponent(25, textureID));
	w->position = Vec3f(0,0,0);

	objects->push_back(w);*/

	/*textureID = textureManager->getTexture(TEXTURE_BALL);
	GameObject* b = new GameObject();

	b->addComponent(new SphereComponent(1, textureID));
	b->position = Vec3f(0,5,0);
	b->tag = "BALL";
	b->velocity = Vec3f(4, -2, 3);
	objects->push_back(b);*/
}

void Scene::setupFloor()
{
	// FLOOR
	GLuint textureID = textureManager->getTexture(TEXTURE_SAND);
	
	const float size = 1;
	const float rows = 5;
	const float columns = 90;
	const float startColumn = -10;
	for (float i = 0 + (size * 2); i < (rows + (size * 2)); i += (size * 2))
	{
		for (float j = startColumn; j < (columns + (size * 2)); j += (size * 2))
		{
			GameObject* floor = new GameObject();
			floor->tag = Tags::FLOOR;
			floor->addComponent(new SlabComponent(size, textureID));
			floor->position = Vec3f(j, 0, i);
			floor->rotation = Vec3f(90,0,0);
			objects->push_back(floor);
		}
	}
}

void Scene::setupCeiling()
{
	// ROOF
	//GLuint textureID = textureManager->getTexture(TEXTURE_FLOOR);

	//const float size = 1;
	//const float rows = 5;
	//const float columns = 90;
	//const float startColumn = -10;
	//for (float i = 0 + (size * 2); i < (rows + (size * 2)); i += (size * 2))
	//{
	//	for (float j = startColumn; j < (columns + (size * 2)); j += (size * 2))
	//	{
	//		GameObject* floor = new GameObject();
	//		floor->tag = Tags::FLOOR;
	//		floor->addComponent(new SlabComponent(size, textureID));
	//		floor->position = Vec3f(j, 0, i);
	//		floor->rotation = Vec3f(90, 0, 0);

	//		objects->push_back(floor);
	//	}
	//}
}