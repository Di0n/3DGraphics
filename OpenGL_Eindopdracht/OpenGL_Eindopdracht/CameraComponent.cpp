#include "CameraComponent.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vec.h"
#include <iostream>
void CameraComponent::update(float elapsedTime)
{

}
void CameraComponent::move(float angle, float fac)
{
	camera->posX += (float)cos((camera->rotY + angle) / 180 * M_PI) * fac;
	camera->posY += (float)sin((camera->rotY + angle) / 180 * M_PI) * fac;

	std::cout << "Cam x: " << camera->posX << std::endl;
	std::cout << "Cam y: " << camera->posY << std::endl;
}

void CameraComponent::moveUp(float s)
{
	camera->posZ = s;
}

Vec3f CameraComponent::getCamPos() const
{
	return Vec3f(camera->posX, camera->posY, camera->posZ);
}

Vec3f CameraComponent::getCamRot() const
{
	return Vec3f(camera->rotX, camera->rotY, camera->rotZ);
}

Camera* CameraComponent::getCam()
{
	return camera;
}