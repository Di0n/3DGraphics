#include "CameraComponent.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
void CameraComponent::update(float elapsedTime)
{
}
void CameraComponent::move(float angle, float fac)
{
	camera->posX += (float)cos((camera->rotY + angle) / 180 * M_PI) * fac;
	camera->posY += (float)sin((camera->rotY + angle) / 180 * M_PI) * fac;
}