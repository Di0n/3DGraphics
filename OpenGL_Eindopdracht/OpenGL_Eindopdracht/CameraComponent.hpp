#pragma once

#include "Component.h"
#include "Camera.hpp"

class CameraComponent : public Component
{
public:
	CameraComponent(Camera* camera) : camera(camera) {}
	~CameraComponent() {};

	void move(float angle, float fac);
	virtual void update(float elapsedTime) override;
private:
	Camera* camera;
};