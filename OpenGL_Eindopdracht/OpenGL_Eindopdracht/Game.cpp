#include "Game.hpp"
#include <list>
#include <vector>
#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <random>

#include "TextureManager.hpp"
#include "Camera.hpp"
#include "GameObject.h"
#include "CubeComponent.h"
#include "CameraComponent.hpp"
#include "PlayerComponent.h"
#include "WallComponent.h"
#include "FloorComponent.hpp"
#include "MoveToComponent.h"
#include "TextureResource.hpp"
#include "Level.hpp"
#include "Scene.hpp"
#include "FrameRateCounter.hpp"
#include "Util.hpp"

using std::string;
using std::vector;
namespace Game
{
	void setUpScene();
	void spawnObstacle();
	int obstacleCount;
	const int MAX_OBSTACLES = 5;

	int windowWidth, windowHeight;
	bool keys[256];
	int keyModifiers;


	TextureManager textureManager;

	// Active world camera
	Camera camera;

	FrameRateCounter frc;
	// Game objects
	//std::list<GameObject*> objects;
	vector<GameObject*> objects;

	// Player object
	GameObject* player;


	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));

		textureManager.addTextureSource(TEXTURE_WALL);
		textureManager.addTextureSource(TEXTURE_FLOOR);
		textureManager.addTextureSource(TEXTURE_THWOMP);
		textureManager.addTextureSource(TEXTURE_CASTLE);
		textureManager.addTextureSource(TEXTURE_BALL);
		textureManager.addTextureSource(TEXTURE_BOX);

		textureManager.load();

		camera = Camera(0, -4, 0, 0, 0, 0);
		//Level level = Level(&camera, &objects, &textureManager);
		//level.setup();
		Scene scene(&camera, &objects, &textureManager);
		scene.setup();
	}
	void update(float deltaTime)
	{
		frc.update(deltaTime);

		vector<GameObject*>::iterator itr = objects.begin();

		while (itr != objects.end())
		{
			auto o = (*itr);
			if (o->tag == "OBSTACLE")
			{
				if (o->position.x <= -15)
				{
					obstacleCount--;
					itr = objects.erase(itr);
					delete o;
					continue;
				}
			}
			o->update(deltaTime);
			++itr;
		}

		if (obstacleCount < MAX_OBSTACLES)
		{
			spawnObstacle();
		}
	}
	float fogCol[3] = { 0.8f, 0.8f, 0.8f };
	void draw()
	{
		// Camera view
		glRotatef(camera.rotX, 1, 0, 0);
		glRotatef(camera.rotY, 0, 1, 0);
		glTranslatef(camera.posX, camera.posZ, camera.posY);
		
		glColor3f(0.5f, 0.8f, 0.2f);
		// Mist
		//glEnable(GL_FOG);
		
		//glFogfv(GL_FOG_COLOR, fogCol);
		//glFogi(GL_FOG_MODE, GL_LINEAR);

		//glFogf(GL_FOG_START, 10.0f);
		//glFogf(GL_FOG_END, 40.0f);

		
		for (const auto& o : objects)
			o->draw();

		//glDisable(GL_FOG);

		float avgFrames = frc.getAverageFramesPerSecond();
		string avgStr = std::to_string(avgFrames);
		string fps = "FPS: " + avgStr.substr(0, avgStr.find_last_of('.'));
		Util::drawText(Util::Color4(255, 255, 255, 1), Vec2f(20, windowHeight - 40), windowWidth, windowHeight, fps);

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

	int getRandomNumber()
	{
		thread_local static std::mt19937 rg{ std::random_device{}() };
		thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, 12);
		return pick(rg);
	}
	void spawnObstacle()
	{
		GameObject* obstacle = new GameObject();
		obstacle->tag = "OBSTACLE";
		float randomZ = getRandomNumber();

		obstacle->position = Vec3f(30, -0.5f, randomZ);
		//obstacle->addComponent(new CubeComponent(0.25f));
		GLuint texture = textureManager.getTexture(TEXTURE_THWOMP);
		obstacle->addComponent(new WallComponent(0.5f, texture));
		MoveToComponent* m = new MoveToComponent();
		m->target = Vec3f(-20, -0.5f, randomZ);
		m->speed = 5;
		obstacle->rotation = Vec3f(0, 90, 0);
		obstacle->addComponent(m);
		obstacleCount++;
		objects.push_back(obstacle);
	}

	void onKey(Key key)
	{
		keys[key] = true;
		keyModifiers = glutGetModifiers();
	}

	void onKeyUp(Key key)
	{
		keys[key] = false;
		keyModifiers = 0;
		//memset(keysJustUp, 0, sizeof(keysJustUp));

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
			const int centerX = windowWidth / 2;
			const int centerY = windowHeight / 2;

			if (x != centerX || y != centerY)
				glutWarpPointer(centerX, centerY);
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