#pragma once

#include "Component.h"
#include "Vec.h"
// Player component to control player.
class PlayerComponent : public Component
{
private:
	float speed = 50;
	void move(float angle, float fac);
	const Vec3f gravity = Vec3f(0.0, -9.81, 0.0);
	const float friction = 0.98;
public:
	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

