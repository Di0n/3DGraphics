#include "CameraComponent.hpp"
#include <GL\freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>
void CameraComponent::update(float elapsedTime)
{

}

void CameraComponent::move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

Camera* CameraComponent::getCamera()
{
	return &camera;
}
