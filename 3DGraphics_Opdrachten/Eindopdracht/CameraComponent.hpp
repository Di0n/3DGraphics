#pragma once
#include "DrawComponent.h"
#include "Camera.hpp"
class CameraComponent : public Component
{
private:
	Camera camera;
public:
	CameraComponent() { camera = Camera(0, -4, 0, 0); }
	CameraComponent(Camera cam) : camera(cam) {}
	~CameraComponent() {}
	
	void move(float angle, float fac);
	virtual void update(float elapsedTime) override;

	Camera* getCamera();
};

