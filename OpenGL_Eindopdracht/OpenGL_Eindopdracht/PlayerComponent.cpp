#include "PlayerComponent.h"
#include <GL\freeglut.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>
#include "CameraComponent.hpp"
#include "GameObject.h"
#include "Game.hpp"
#include "MoveToComponent.h"
#include "GravityComponent.hpp"


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
	CameraComponent* camera = gameObject->getComponent<CameraComponent>();
	if (!camera) return;

	Camera* cam = camera->getCam();
	
	handleInput(elapsedTime, cam);

	gameObject->velocity += GRAVITY * elapsedTime;
	gameObject->velocity.x *= FRICTION;
	gameObject->velocity.z *= FRICTION;

	Vec3f newPos = gameObject->position + gameObject->velocity * elapsedTime;
	Vec3f oldPos = gameObject->position;
	gameObject->position = newPos;

	// Check bounds
	if (gameObject->position.y < 0)
	{
		gameObject->position.y = oldPos.y;
	}
	
	cam->posX = -gameObject->position.x;
	cam->posY = -(gameObject->position.z + 0.8f);
	cam->posZ = -gameObject->position.y;
	///gameObject->position.x = -(camPos.x + 0.0);
	///gameObject->position.z = -(camPos.y - 0.8);
}

void PlayerComponent::handleInput(float elapsedTime, Camera* cam)
{
	static Key prevKey = 0;
	const SHORT shiftPressed = GetKeyState(VK_LSHIFT);

	float correctedSpeed = elapsedTime * ((shiftPressed < 0) ? runSpeed : speed);

	if (Game::keys[VK_SPACE])
	{
		prevKey = VK_SPACE;
	}
	else if (prevKey == VK_SPACE)
	{
		gameObject->velocity.y = JUMP_VELOCITY; //= Vec3f(0,2.0f, 0);
		prevKey = 0;
	}

	if (Game::keys['w'])
		move(cam, ANGLE_W, correctedSpeed);
	if (Game::keys['s'])
	{
		move(cam, ANGLE_S, correctedSpeed);
		if (gameObject->position.y < MIN_HEIGHT_MOVE)
		{
			
		}
	}
	if (Game::keys['a'])
		move(cam, ANGLE_A, correctedSpeed);
	if (Game::keys['d'])
		move(cam, ANGLE_D, correctedSpeed);
}

void PlayerComponent::move(Camera* cam, float angle, float speed)
{
	float xVel = -(float)cos((cam->rotY + angle) / 180 * M_PI) * speed;
	float zVel = -(float)sin((cam->rotY + angle) / 180 * M_PI) * speed;
	gameObject->velocity.x += xVel;
	gameObject->velocity.z += zVel;
}
