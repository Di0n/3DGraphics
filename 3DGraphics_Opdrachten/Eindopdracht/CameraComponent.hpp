#pragma once
#include "DrawComponent.h"
#include "Camera.hpp"
class CameraComponent : public DrawComponent
{
public:
	CameraComponent(Camera cam) : camera(cam) {}
	~CameraComponent() {}
	
	Camera camera;
	void move(float angle, float fac);
	virtual void update(float elapsedTime) override;
	virtual void draw() override;
};

