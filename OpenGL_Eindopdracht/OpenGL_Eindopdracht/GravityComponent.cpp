#include "GravityComponent.hpp"
#include "GameObject.h"
#include <iostream>
void GravityComponent::update(float elapsedTime)
{
	//if (gameObject->position.y == 0) return;
	//float fallingSpeed = acceleration * elapsedTime;

	float pos = elapsedTime * (gameObject->velocity.y + elapsedTime * acceleration / 2);
	gameObject->velocity.y += elapsedTime * acceleration;
	
	gameObject->position.y += pos;

	gameObject->position.y = (gameObject->position.y < 0) ? 0 : gameObject->position.y;
}