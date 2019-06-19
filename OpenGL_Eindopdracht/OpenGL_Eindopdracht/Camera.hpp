#pragma once
struct Camera
{
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	Camera() :posX(0), posY(0), posZ(0), rotX(0), rotY(0), rotZ(0) {}
	Camera(float posX, float posY, float posZ, float rotX, float rotY, float rotZ) 
		: posX(posX), posY(posY), posZ(posZ), rotX(rotX), rotY(rotY), rotZ(rotZ) {}
};