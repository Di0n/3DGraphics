#include "PlayerComponent.h"
#include "CameraComponent.hpp"
#include "GameObject.h"
#include "Game.hpp"
#include "MoveToComponent.h"
#include "GravityComponent.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

PlayerComponent::PlayerComponent()
{
	
}

PlayerComponent::~PlayerComponent()
{
}

void m(Camera* cam, float angle, float speed)
{
	float xVel = -(float)cos((cam->rotY + angle) / 180 * M_PI) * speed;
	float zVel = -(float)sin((cam->rotY + angle) / 180 * M_PI) * speed;
}

void PlayerComponent::update(float elapsedTime)
{
	const float correctedSpeed = elapsedTime * speed;

	CameraComponent* camera = gameObject->getComponent<CameraComponent>();
	if (!camera) return;
	static Key prevKey = 0;
	Camera* cam = camera->getCam();

	if (Game::keys[0x20])
	{
		prevKey = 0x20;
	}
	else if (prevKey == 0x20)
	{
		// Jump
		
		//camera->move(20, correctedSpeed);
		//gameObject->position.y += correctedSpeed;
		gameObject->velocity.y = 4.0f; //= Vec3f(0,2.0f, 0);
		
		//camera->moveUp(correctedSpeed * 40);
		//gameObject->getComponent<Grav
		prevKey = 0;
	}
	if (Game::keys['z'])
	{
		prevKey = 'z';
	}
	else if (prevKey == 'z')
	{
		camera->moveUp(-(correctedSpeed * 40));
		prevKey = 0;
	}
	if (Game::keys['w'])
	{
		//gameObject->position.z -= correctedSpeed;
		//camera->move(90, correctedSpeed);
		float xVel = -(float)cos((cam->rotY + 90) / 180 * M_PI) * correctedSpeed;
		float zVel = -(float)sin((cam->rotY + 90) / 180 * M_PI) * correctedSpeed;
		gameObject->velocity.x += xVel ;
		gameObject->velocity.z += zVel ;
		//std::cout << "XW: " << xVel << std::endl;
		//std::cout << "ZW: " << zVel << std::endl;
	}
	if (Game::keys['s'])
	{
		//gameObject->position.z += correctedSpeed;
		//camera->move(270, correctedSpeed);
		if (gameObject->position.y < 0.01)
		{
			float xVel = -(float)cos((cam->rotY + 270) / 180 * M_PI) * correctedSpeed;
			float zVel = -(float)sin((cam->rotY + 270) / 180 * M_PI) * correctedSpeed;
			gameObject->velocity.x += xVel;
			gameObject->velocity.z += zVel;
		}
		//std::cout << "XS: " << xVel << std::endl;
		//std::cout << "ZS: " << zVel << std::endl;
	}
	if (Game::keys['a'])
	{
		//gameObject->position.x -= correctedSpeed;
		//camera->move(0, correctedSpeed);
		float xVel = -(float)cos((cam->rotY + 0) / 180 * M_PI) * correctedSpeed;
		float zVel = -(float)sin((cam->rotY + 0) / 180 * M_PI) * correctedSpeed;
		gameObject->velocity.x += xVel;
		gameObject->velocity.z += zVel;
	}
	if (Game::keys['d'])
	{
		//gameObject->position.x += correctedSpeed;
		//camera->move(180, correctedSpeed);
		float xVel = -(float)cos((cam->rotY + 180) / 180 * M_PI) * correctedSpeed;
		float zVel = -(float)sin((cam->rotY + 180) / 180 * M_PI) * correctedSpeed;
		gameObject->velocity.x += xVel;
		gameObject->velocity.z += zVel;
	}

	Vec3f camPos = camera->getCamPos();
	
	
	//gameObject->position.y = -(camPos->z);
	//gameObject->position.y += gameObject->velocity.y * elapsedTime;
	//float pos = elapsedTime * (gameObject->velocity.y + elapsedTime * acceleration / 2);
	///gameObject->velocity.y += gravity * elapsedTime;
	//gameObject->position.y += gameObject->velocity.y * elapsedTime;
	


	gameObject->velocity += gravity * elapsedTime;
	gameObject->velocity.x *= friction;
	gameObject->velocity.z *= friction;


	Vec3f newPos = gameObject->position + gameObject->velocity * elapsedTime;
	Vec3f oldPos = gameObject->position;
	gameObject->position = newPos;
	if (gameObject->position.y < 0)
	{
		gameObject->position.y = oldPos.y;
	}
	
	cam->posX = -gameObject->position.x;
	cam->posY = -(gameObject->position.z + 0.8);
	///gameObject->position.x = -(camPos.x + 0.0);
	///gameObject->position.z = -(camPos.y - 0.8);

	camera->moveUp(-gameObject->position.y);


	//gameObject->velocity.x += (gameObject->velocity.x < 0) ? 0.01 : -0.01;
	//gameObject->velocity.z += (gameObject->velocity.z < 0) ? 0.01 : -0.01;
	




	/*if (gameObject->velocity.x < 0.0)
	{
		float diff =  gameObject->velocity.x - 0.0;
		if (diff != 0)
			gameObject->velocity.x += diff / 10;
	}
	else if (gameObject->velocity.x > 0.0)
	{
		float diff = 
	}
	if (gameObject->velocity.z )*/

	
}

void PlayerComponent::move(float angle, float speed)
{
	
}
