#include "Game.hpp"
#include <iostream>
#include <GL\freeglut.h>
#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include <list>

namespace Game
{
	Camera camera;
	int windowWidth, windowHeight;
	bool keys[256];
	std::list<GameObject*> objects;
	
	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));
		camera = Camera(0, -4, 0, 0);

		GameObject* o = new GameObject();
		o->addComponent(new CubeComponent(50));

		o->position = Vec3f(-15, -1, -15);
		objects.push_back(o);
	}
	void update(float deltaTime)
	{

	}
	void draw()
	{
		glRotatef(camera.rotX, 1, 0, 0);
		glRotatef(camera.rotY, 0, 1, 0);
		glTranslatef(camera.posX, 0, camera.posY);

	}

	void onKey(Key key)
	{
		keys[key] = true;
	}

	void onKeyUp(Key key)
	{
		keys[key] = false;
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
}