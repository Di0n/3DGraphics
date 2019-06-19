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
#include "AudioComponent.hpp"
#include "HitboxComponent.hpp"
#include "TextureResource.hpp"
#include "Level.hpp"
#include "Scene.hpp"
#include "FrameRateCounter.hpp"
#include "Tags.hpp"
#include "Util.hpp"
#include "SoundPlayer.hpp"
#include "MusicResources.hpp"
#include "ObjectSpawner.hpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;
namespace Game
{
	void spawnObstacle();
	const int MAX_OBSTACLES = 20;

	int windowWidth, windowHeight;
	bool keys[256];
	int keyModifiers;
	
	TextureManager textureManager;

	SoundPlayer* soundPlayer;

	// Active world camera
	Camera camera;

	FrameRateCounter frc;
	// Game objects
	//std::list<GameObject*> objects;
	vector<GameObject*> objects;

	// Player object
	GameObject* player;
	HitboxComponent* playerHitbox;

	int obstacleCount;
	const float DESPAWN_POS = 5.0f;

	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));

		textureManager.addTextureSource(TEXTURE_WALL);
		textureManager.addTextureSource(TEXTURE_FLOOR);
		textureManager.addTextureSource(TEXTURE_BALL);
		textureManager.addTextureSource(TEXTURE_BOX);
		textureManager.addTextureSource(TEXTURE_SAND);
		textureManager.addTextureSource(TEXTURE_WALL_1);
		textureManager.addTextureSource(TEXTURE_FINISH);




		textureManager.load();
		
		soundPlayer = &SoundPlayer::getInstance();
		soundPlayer->addSound(MusicResources::DEATH_SOUND, Tags::DEATH_SOUND, true);
		//soundPlayer->addSound(MusicResources::DEATH_SOUND, "TEST", true);

		camera = Camera(0, -4, 0, 0, 0, 0);

		//Level level = Level(&camera, &objects, &textureManager);
		//level.setup();
		Scene scene(&camera, &objects, &textureManager);
		scene.setup();
		for (auto o : objects)
		{
			if (o->tag == Tags::PLAYER)
			{
				player = o;
				playerHitbox = player->getComponent<HitboxComponent>();
				break;
			}
		}
	}

	long long hitcount = 0;
	int spawn = 0;
	void update(float deltaTime)
	{
		frc.update(deltaTime);

		vector<GameObject*>::iterator itr = objects.begin();

		while (itr != objects.end())
		{
			auto o = (*itr);
			if (o->tag == Tags::OBSTACLE)
			{
				if (o->position.x < (player->position.x - DESPAWN_POS))
				{
					obstacleCount--;
					itr = objects.erase(itr);
					delete o;
					continue;
				}
				auto hitbox = o->getComponent<HitboxComponent>();
				if (hitbox->collided(playerHitbox))
				{
					cout << "Hit: " << hitcount++ << endl;
					auto ac = player->getComponent<AudioComponent>();
					ac->playSound(false);
				}
			}
			else if (o == player)
			{
				soundPlayer->setListenerPosition(player->position, player->rotation);
			}
			else if (o->tag == "BALL")
			{
				o->position += o->velocity * deltaTime;

				if (o->position.y <= 0)
				{
					o->velocity.y *= -1;
				}
				else if (o->position.y > 20)
				{
					o->velocity.y *= -1;
				}
				if (o->position.x < -20)
					o->velocity.x *= -1;
				else if (o->position.x > 20)
					o->velocity.x *= -1;
				if (o->position.z< -20)
					o->velocity.z *= -1;
				else if (o->position.z > 20)
					o->velocity.z *= -1;
			}
			o->update(deltaTime);
			++itr;
			spawn++;
		}

		if (obstacleCount < MAX_OBSTACLES && spawn  > 20000)
		{
			spawnObstacle();
			spawn = 0;
		}
	}
	float fogCol[3] = { 0.8f, 0.8f, 0.8f };
	float fogStart = 2.0f;
	float fogEnd = 60.0f;
	void draw()
	{
		// Camera view
		glRotatef(camera.rotX, 1, 0, 0);
		glRotatef(camera.rotY, 0, 1, 0);
		glTranslatef(camera.posX, camera.posZ, camera.posY);
		
		//glColor3f(0.5f, 0.8f, 0.2f);
		// Mist

		glEnable(GL_FOG);
		
		glFogfv(GL_FOG_COLOR, fogCol);
		glFogi(GL_FOG_MODE, GL_LINEAR);

		glFogf(GL_FOG_START, 2.0f);
		glFogf(GL_FOG_END, 20.0f);
		
		
		for (const auto& o : objects)
			o->draw();

		glDisable(GL_FOG);

		float avgFrames = frc.getAverageFramesPerSecond();
		string avgStr = std::to_string(avgFrames);
		string fps = "FPS: " + avgStr.substr(0, avgStr.find_last_of('.'));
		Util::drawText(Util::Color4(255, 255, 255, 1), Vec2f(20, windowHeight - 40), windowWidth, windowHeight, fps);

			//glBegin(GL_QUADS);
			//glVertex3f(-15, -1, -15);
			//glVertex3f(15, -1, -15);
			//glVertex3f(15, -1, 15);
			//glVertex3f(-15, -1, 15);
			//glEnd();
	}
	
	void spawnObstacle()
	{
		static ObjectSpawner spawner = ObjectSpawner(&textureManager);
		objects.push_back(spawner.spawnRandomObstacle(player->position.x + 30));
		obstacleCount++;
		//GameObject* obstacle = new GameObject();
		//obstacle->tag = Tags::OBSTACLE;
		//float randomZ = 2; //Util::getRandomNumber<int>(2, 6);

		//obstacle->position = Vec3f(30, -0.5f, randomZ);
		////obstacle->addComponent(new CubeComponent(0.25f));
		//GLuint texture = textureManager.getTexture(TEXTURE_BOX);
		////obstacle->addComponent(new WallComponent(0.5f, texture));
		//obstacle->addComponent(new CubeComponent(0.5f, texture));
		//obstacle->addComponent(new HitboxComponent(0.5f, 0.5f, 0.5f));
		//MoveToComponent* m = new MoveToComponent();
		//m->target = Vec3f(-20, -0.5f, randomZ);
		//m->speed = 5;
		//obstacle->rotation = Vec3f(0, 90, 0);
		//obstacle->addComponent(m);
		//obstacleCount++;
		//objects.push_back(obstacle);
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
		case 'z':

			fogStart += 1.0f;
			break;
		case 'x':
			fogEnd -= 0.5f; 
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
}