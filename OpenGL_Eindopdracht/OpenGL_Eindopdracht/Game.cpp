#include "Game.hpp"
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
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

#define FOG
using std::string;
using std::vector;
using std::cout;
using std::endl;
namespace Game
{
	void spawnObstacle();
	void gameStart();
	void gameOver(int reason);
	void drawResult();
	void drawHighscore();



	const int MAX_OBSTACLES = 30;
	const float DESPAWN_POS = 5.0f;
	const float SPAWN_STOP = 15.0f;
	const int TIME_BETWEEN_SPAWNS = 150;
	const float DRAW_DISTANCE = 5000.0f;
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
	int lastHit;
	int startTime;
	int endTime;
	int result;
	irrklang::ISound* gameSound;


	void loadContent()
	{
		ZeroMemory(keys, sizeof(keys));

		textureManager.addTextureSource(TEXTURE_WALL);
		textureManager.addTextureSource(TEXTURE_FLOOR);
		textureManager.addTextureSource(TEXTURE_BALL);
		textureManager.addTextureSource(TEXTURE_MBOX);
		textureManager.addTextureSource(TEXTURE_EMPBOX);
		textureManager.addTextureSource(TEXTURE_WBOX);
		textureManager.addTextureSource(TEXTURE_SAND);
		textureManager.addTextureSource(TEXTURE_WALL_1);
		textureManager.addTextureSource(TEXTURE_FINISH);
		textureManager.addTextureSource(TEXTURE_DIED_SCREEN);
		textureManager.addTextureSource(TEXTURE_STARS);


		textureManager.load();
		
		soundPlayer = &SoundPlayer::getInstance();
		soundPlayer->addSound(MusicResources::DEATH_SOUND, Tags::DEATH_SOUND, true);
		soundPlayer->addSound(MusicResources::ELECTRICAL_SOUND, MusicResources::ELECTRICAL_SOUND, true);
		soundPlayer->addSound(MusicResources::GAME_MUSIC, MusicResources::GAME_MUSIC, true);

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
		obstacleCount = 0;
		while (itr != objects.end())
		{
			auto o = (*itr);
			o->update(deltaTime);
			if (o->tag == Tags::OBSTACLE || o->tag == Tags::EMP)
			{
				obstacleCount++;
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
					
					if (o->tag == Tags::OBSTACLE)
					{
						auto ac = player->getComponent<AudioComponent>();
						ac->playSound(false);
						status = PLAYER_DIED;
						break;
					}
					else if (o->tag == Tags::EMP)
					{
						toggleLight = false;
					}
				}
			}
			else if (o == player)
			{
				soundPlayer->setListenerPosition(player->position, Vec3f(-camera.rotX, -camera.rotY,- camera.rotZ));
				if (player->position.x >= 90)
				{
					gameOver(PLAYER_WON);
				}
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
			
			++itr;
		}

		if (status == PLAYER_DIED)
		{
			toggleLight = true;
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
				&& (90 - fabsf(player->position.x)) > SPAWN_STOP)
			{
				spawnObstacle();
				lastSpawnTime = currentTime;
			}
		}
	}
	float fogCol[3] = { 0.8f, 0.8f, 0.8f };
	void draw()
	{
		const int currentTime = glutGet(GLUT_ELAPSED_TIME);

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

#ifdef FOG
		glEnable(GL_FOG);
		
		glFogfv(GL_FOG_COLOR, fogCol);
		glFogi(GL_FOG_MODE, GL_LINEAR);

		glFogf(GL_FOG_START, 2.0f);
		glFogf(GL_FOG_END, 20.0f);
#endif

		for (const auto& o : objects)
		{
			if (o->position.distance(player->position) <= DRAW_DISTANCE)
				o->draw();
		}
#ifdef FOG
		glDisable(GL_FOG);
#endif

		if (drawEndScreen)
		{
			drawResult();
			drawHighscore();
		}
		

		float avgFrames = frc.getAverageFramesPerSecond();
		string avgStr = std::to_string(avgFrames);
		string fps = "FPS: " + avgStr.substr(0, avgStr.find_last_of('.'));

		//string text = fps + ("\nObjects: " + obstacleCount);
		Util::drawText(Util::Color4(255, 255, 255, 1), Vec2f(20, windowHeight - 40), windowWidth, windowHeight, fps);
		
		if (gameStarted)
		{
			int remaining = currentTime - startTime;

			int minutes, seconds;
			Util::toTime(remaining, &minutes, &seconds);
			string time = std::to_string(minutes) + ':' + std::to_string(seconds);
			Util::drawText(Util::Color4(255, 255, 255, 1), Vec2f(windowWidth - 70, windowHeight - 40), windowWidth, windowHeight, time);
		}
			//glBegin(GL_QUADS);
			//glVertex3f(-15, -1, -15);
			//glVertex3f(15, -1, -15);
			//glVertex3f(15, -1, 15);
			//glVertex3f(-15, -1, 15);
			//glEnd();
	}

	void drawResult()
	{
		int minutes, seconds;
		Util::toTime(endTime, &minutes, &seconds);

		if (result == PLAYER_DIED)
		{
			const string text = "YOU DIED\nYou survived: " + std::to_string(minutes) +
				" minutes and " + std::to_string(seconds) + " seconds\nPress Enter to restart.";
			Util::drawText(Util::Color4(255, 0, 0, 1), Vec2f((windowWidth / 2 - 100), (windowHeight / 2 - 40)), windowWidth, windowHeight, text);
		}
		else
		{
			const string text = "YOU WON\nTime: " + std::to_string(minutes) +
				" minutes and " + std::to_string(seconds) + " seconds\nPress Enter to restart.";
			Util::drawText(Util::Color4(255, 215, 0, 1), Vec2f((windowWidth / 2 - 100), (windowHeight / 2 - 40)), windowWidth, windowHeight, text);
		}
	}
	

	void setHighScore(int minutes, int seconds)
	{
		std::ofstream file("hs.score", std::ofstream::out | std::ofstream::trunc);
		if (file.is_open())
		{
			file << std::to_string(minutes) << '\n';
			file << std::to_string(seconds);
		}
	}
	void drawHighscore()
	{
		// Schrijf leaderboards op scherm
		static int hsMin = -1, hsSec = - 1;

		if (hsMin == -1 || hsSec == -1)
		{
			std::ifstream file("hs.score", std::ifstream::in);
			if (file.is_open())
			{
				string line;
				int i = 0;
				while (std::getline(file, line))
				{
					const int nr = std::stoi(line, nullptr);
					if (i++ == 0)
						hsMin = nr;
					else
					{
						hsSec = nr;
						break;
					}
				}
			}
			else
			{
				if (result != PLAYER_WON) return;
				int m, s;
				Util::toTime(endTime, &m, &s);
				setHighScore(m, s);
				hsMin = m;
				hsSec = s;
			}
		}
		else if (result == PLAYER_WON)
		{
			int m, s;
			Util::toTime(endTime, &m, &s);

			if (m <= hsMin && s < hsSec)
			{
				hsMin = m;
				hsSec = s;
				setHighScore(hsMin, hsSec);
			}
		}

		string text = "Highscore: " + std::to_string(hsMin) + " minutes and "+ std::to_string(hsSec) + " seconds.";
		Util::drawText(Util::Color4(255, 215, 0, 1), Vec2f((windowWidth/2) -100, (windowHeight / 2) - 200),
			windowWidth, windowHeight, text);
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
		lastHit = 0;
		startTime = glutGet(GLUT_ELAPSED_TIME);
		endTime = 0;
		result = 0;
		gameSound = soundPlayer->playSound(MusicResources::GAME_MUSIC, true);
		gameSound->setVolume(0.3f);
	}

	void gameOver(int reason)
	{
		gameStarted = false;
		endTime = (glutGet(GLUT_ELAPSED_TIME)) - startTime;
		if (gameSound)
		{
			gameSound->setIsPaused(true);
			gameSound->drop();
			gameSound = nullptr;
		}

		result = reason;
		if (reason == PLAYER_DIED)
		{
			drawEndScreen = true;
			
			cout << "You died\n";
		}
		else if (reason == PLAYER_WON)
		{
			drawEndScreen = true;
			cout << "You won\n";
		}
	}
	
	void spawnObstacle()
	{
		static ObjectSpawner spawner = ObjectSpawner(&textureManager);
		const int nr = Util::getRandomNumber<int>(0, 19);
		ObjectSpawner::ObjectType type;
		if (nr == 0)
			type = ObjectSpawner::Light;
		else
			type = ObjectSpawner::Obstacle;
		objects.push_back(spawner.spawnRandomObstacle(player->position.x + 30, type));
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
			cout << "Pos z: " << player->position.z << "\n";
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