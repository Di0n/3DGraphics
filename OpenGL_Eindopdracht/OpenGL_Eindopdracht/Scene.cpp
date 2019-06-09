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
#include "Tags.hpp"

void Scene::setup()
{
	// PLAYER
	GameObject* player = new GameObject();
	player->tag = Tags::PLAYER;
	player->addComponent(new PlayerComponent());
	//player->addComponent(new CubeComponent(0.3f,5));
	player->addComponent(new CameraComponent(camera));
	player->addComponent(new HitboxComponent(0.3f, 0.3f, 0.3f));
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
	GLuint textureID = textureManager->getTexture(TEXTURE_FLOOR);
	
	const float size = 1;
	const float rows = 5;
	const float columns = 10;

	for (float i = 0 + (size * 2); i < (rows + (size * 2)); i += (size * 2))
	{
		for (float j = -columns; j < (columns + (size * 2)); j += (size * 2))
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

}