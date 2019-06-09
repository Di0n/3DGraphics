#include "HitboxComponent.hpp"
#include <math.h>
#include "GameObject.h"

void HitboxComponent::update(float elapsedTime)
{
}

bool HitboxComponent::collided(const HitboxComponent* hitbox) const
{
	
	if (fabsf(gameObject->position.x - hitbox->gameObject->position.x)
		< sizeX + hitbox->getSizeX())
	{
		if (fabsf(gameObject->position.y - hitbox->gameObject->position.y)
			< sizeY + hitbox->getSizeY())
		{
			if (fabsf(gameObject->position.z - hitbox->gameObject->position.z)
				< sizeZ + hitbox->getSizeZ())
				return true;
		}
	}
	return false;
}
