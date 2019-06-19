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
	void gameStart();
	void gameOver(int reason);

	const int MAX_OBSTACLES = 30;
	const float DESPAWN_POS = 5.0f;
	const int TIME_BETWEEN_SPAWNS = 100;
	const float DRAW_DISTANCE = 50.0f;
	const int PLAYER_DIED = 1;
	const int PLAYER_WON = 2;

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
	bool toggleLight = true;
	bool gameStarted = false;
	bool drawEndScreen = false;


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
		textureManager.addTextureSource(TEXTURE_DIED_SCREEN);

		textureManager.load();
		
		soundPlayer = &SoundPlayer::getInstance();
		soundPlayer->addSound(MusicResources::DEATH_SOUND, Tags::DEATH_SOUND, true);
		//soundPlayer->addSound(MusicResources::DEATH_SOUND, "TEST", true);

		camera = Camera(0, -4, 0, 0, 0, 0);

		//Level level = Level(&camera, &objects, &textureManager);
		//level.setup();
		gameStart();
	}

	long long hitcount = 0;
	int lastSpawnTime;
	void update(float deltaTime)
	{
		frc.update(deltaTime);

		if (!gameStarted) return;
		vector<GameObject*>::iterator itr = objects.begin();

		int status = 0;
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
					status = PLAYER_DIED;
					break;
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
		}

		if (status == PLAYER_DIED)
		{
			gameOver(PLAYER_DIED);
		}
		else if (status == PLAYER_WON)
		{
			gameOver(PLAYER_WON);
		}
		else
		{
			int currentTime = glutGet(GLUT_ELAPSED_TIME);
			if (obstacleCount < MAX_OBSTACLES && ((currentTime - lastSpawnTime) >= TIME_BETWEEN_SPAWNS)
				&& (90 - fabsf(player->position.x)) > 5)
			{
				spawnObstacle();
				lastSpawnTime = currentTime;
			}
		}
	}
	float fogCol[3] = { 0.8f, 0.8f, 0.8f };
	void draw()
	{
		// Camera view
		glRotatef(camera.rotX, 1, 0, 0);
		glRotatef(camera.rotY, 0, 1, 0);
		glTranslatef(camera.posX, camera.posZ, camera.posY);
		
		//glColor3f(0.5f, 0.8f, 0.2f);
		// Mist

		if (!toggleLight)
		{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			//GLfloat light_position[] = { 0.0, 0.0, 0.0, 1 };
			GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1 };

			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			GLfloat lightDiff[] = { 1.0, 1.0, 1.0, 1.0 };
			glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
			GLfloat lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
		}
		else
		{
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}

		glEnable(GL_FOG);
		
		glFogfv(GL_FOG_COLOR, fogCol);
		glFogi(GL_FOG_MODE, GL_LINEAR);

		glFogf(GL_FOG_START, 2.0f);
		glFogf(GL_FOG_END, 20.0f);
		

		for (const auto& o : objects)
		{
			if (o->position.distance(player->position) <= DRAW_DISTANCE)
				o->draw();
		}

		glDisable(GL_FOG);

		if (drawEndScreen)
		{
			const string text = "YOU DIED\nPress Enter to restart.";
			Util::drawText(Util::Color4(255, 0, 0, 1), Vec2f((windowWidth / 2 - 40), (windowHeight / 2 - 40)), windowWidth, windowHeight, text);
		}
		

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

	void gameStart()
	{
		for (auto o : objects)
		{
			if (o)
			{
				delete o;
			}
		}
		objects.clear();

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
		toggleLight = true;
		lastSpawnTime = 0;
		obstacleCount = 0;
		gameStarted = true;
		drawEndScreen = false;
	}

	void gameOver(int reason)
	{
		gameStarted = false;

		if (reason == PLAYER_DIED)
		{
			drawEndScreen = true;

			cout << "You died\n";
		}
		else if (reason == PLAYER_WON)
			cout << "You won\n";

	}
	
	void spawnObstacle()
	{
		static ObjectSpawner spawner = ObjectSpawner(&textureManager);
		objects.push_back(spawner.spawnRandomObstacle(player->position.x + 30, ObjectSpawner::ObjectType::Obstacle));
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
			toggleLight = !toggleLight;
			break;
		case VK_RETURN:
			
			if (!gameStarted)
			{
				gameStart();
			}
			break;
		default:
			break;
		}
	}

	void onMouseMove(int x, int y)
	{
		if (!gameStarted) return;
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