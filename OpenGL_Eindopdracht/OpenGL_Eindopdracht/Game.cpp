#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "TextureManager.hpp"
#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "CameraComponent.hpp"
#include "PlayerComponent.h"
#include "WallComponent.h"
#include "FloorComponent.hpp"
#include "TextureResource.hpp"
#include "Level.hpp"

namespace Game
{
	void setUpScene();

	int windowWidth, windowHeight;
	bool keys[256];

	TextureManager textureManager;
	
	// Active world camera
	Camera camera;

	// Game objects
	std::list<GameObject*> objects;
	
	// Player object
	GameObject* player;

	
	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));
		
		textureManager.addTextureSource(TEXTURE_WALL);
		textureManager.addTextureSource(TEXTURE_FLOOR);
		textureManager.addTextureSource(TEXTURE_TABLE);
		textureManager.load();

		camera = Camera(0,-4,0,0,0,0);
		Level level = Level(&camera, &objects, &textureManager);
		level.setup();
	}
	void update(float deltaTime)
	{
		for (const auto& o : objects)
			o->update(deltaTime);
	}
	void draw()
	{
		// Camera view
		glRotatef(camera.rotX, 1, 0, 0);
		glRotatef(camera.rotY, 0, 1, 0);
		glTranslatef(camera.posX, camera.posZ, camera.posY);


		glColor3f(0.5f, 0.8f, 0.2f);
		for (const auto& o : objects)
			o->draw(); 

		// Floor
		/*glColor3f(0.1f, 1.0f, 0.2f);
		glBegin(GL_QUADS);
		glVertex3f(-15, -1, -15);
		glVertex3f(15, -1, -15);
		glVertex3f(15, -1, 15);
		glVertex3f(-15, -1, 15);
		glEnd();

		glColor3f(0.5f, 0.8f, 0.2f);
		for (const auto& o : objects)
			o->draw();*/



		//glBegin(GL_QUADS);
		//glVertex3f(-15, -1, -15);
		//glVertex3f(15, -1, -15);
		//glVertex3f(15, -1, 15);
		//glVertex3f(-15, -1, 15);
		//glEnd();
	}

	void onKey(Key key)
	{
		keys[key] = true;
	}

	void onKeyUp(Key key)
	{
		keys[key] = false;

		switch (key)
		{
		case VK_ESCAPE:
			glutLeaveMainLoop();
			break;
		default:
			break;
		}
	}

	void onMouseMove(int x, int y)
	{
		static bool justMoved = false;

		if (justMoved)
		{
			justMoved = false;
			return;
		}
		int dx = x - windowWidth / 2;
		int dy = y - windowHeight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			camera.rotY += dx / 10.0f;
			camera.rotX += dy / 10.0f;
			glutWarpPointer(windowWidth / 2, windowHeight / 2);
			justMoved = true;
		}
	}

	void onResize(int w, int h)
	{
		windowWidth = w;
		windowHeight = h;
	}

	void onClose()
	{
		std::cout << "Cleaning up game\n";
		for (auto& o : objects)
			delete o;
		objects.clear();

		std::cout << "Closing game.\n";
	}

	void createWalls()
	{

	}

	void createFloor()
	{

	}
	void setUpScene()
	{
		camera = Camera(0, -4, 0, 0, 0, 0);

		//// PLAYER
		//player = new GameObject();
		//player->addComponent(new PlayerComponent());
		//player->addComponent(new CameraComponent(&camera));

		//player->position = Vec3f(0, 0, 0);

		//// TEST
		//GameObject* o = new GameObject();
		//o->addComponent(new CubeComponent(0.5));
		//o->position = Vec3f(0, 4, 0);

		//// BACK WALLS
		//GLuint textureID;
		//textureManager.getTexture(TEXTURE_WALL, &textureID);
		//GameObject* wallObject = new GameObject();
		//wallObject->addComponent(new WallComponent(1, textureID));
		//wallObject->position = Vec3f(0, 0, 0);

		//// FLOOR
		//textureManager.getTexture(TEXTURE_FLOOR, &textureID);
		//GameObject* floor = new GameObject();
		//floor->addComponent(new FloorComponent(1, textureID));
		//floor->position = Vec3f(0, 0, 2);

		//// TABLE
		//textureManager.getTexture(TEXTURE_TABLE, &textureID);
		//GameObject* table = new GameObject();

		//

		//objects.push_back(o);
		//objects.push_back(wallObject);
		//objects.push_back(floor);
		//objects.push_back(player);
	}
}