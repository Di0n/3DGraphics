#include "PlayerComponent.h"
#include "CameraComponent.hpp"
#include "GameObject.h"
#include "Game.hpp"


PlayerComponent::PlayerComponent()
{
	
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float elapsedTime)
{
	const float correctedSpeed = elapsedTime * speed;

	CameraComponent* camera = gameObject->getComponent<CameraComponent>();
	if (!camera) return;

	if (Game::keys['w'])
	{
		gameObject->position.z -= correctedSpeed;
		camera->move(90, correctedSpeed);
	}
	if (Game::keys['s'])
	{
		gameObject->position.z += correctedSpeed;
		camera->move(270, correctedSpeed);

	}
	if (Game::keys['a'])
	{
		gameObject->position.x -= correctedSpeed;
		camera->move(0, correctedSpeed);
	}
	if (Game::keys['d'])
	{
		gameObject->position.x += correctedSpeed;
		camera->move(180, correctedSpeed);
	}
}

void PlayerComponent::move(float angle, float fac)
{

}
