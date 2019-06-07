#pragma once

#include "Component.h"
#include "Camera.hpp"
class Vec3f;
class CameraComponent : public Component
{
public:
	CameraComponent(Camera* camera) : camera(camera) {}
	~CameraComponent() {};

	void move(float angle, float fac);
	void moveUp(float s);
	virtual void update(float elapsedTime) override;

	Vec3f getCamPos() const;
	Vec3f getCamRot() const;
	Camera* getCam();
private:
	Camera* camera;
};