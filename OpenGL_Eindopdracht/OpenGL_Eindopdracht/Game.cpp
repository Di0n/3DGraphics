#include "Game.hpp"
#include <list>
#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "PlayerComponent.h"

namespace Game
{
	int windowWidth, windowHeight;
	bool keys[256];

	// Active world camera
	Camera camera;

	// Game objects
	std::list<GameObject*> objects;
	
	// Player object
	GameObject* player;


	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));

		camera = Camera(0, -4, 0, 0, 0, 0);
		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(0.5));

		o->position = Vec3f(0, 4, 0);
		player = new GameObject();
		player->addComponent(new PlayerComponent());

		player->position = Vec3f(0, 0, 0);
		
		objects.push_back(o);
		objects.push_back(player);
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


		//glColor3f(0.5f, 0.8f, 0.2f);
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
}