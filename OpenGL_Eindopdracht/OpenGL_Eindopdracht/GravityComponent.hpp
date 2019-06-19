#pragma once

#include "Component.h"

class GravityComponent : public Component
{
public:
	GravityComponent(float gravity = 9.81) : acceleration(gravity) {}
	~GravityComponent() {};

	virtual void update(float elapsedTime) override;
private:
	float acceleration;
};