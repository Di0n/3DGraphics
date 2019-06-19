#pragma once

#include "Component.h"
#include "Vec.h"

// Component to make object move to position
class MoveToComponent : public Component
{
public:
	float speed = 10;// 0.025f;
	Vec3f target;

	MoveToComponent();
	~MoveToComponent();

	virtual void update(float elapsedTime) override;
};

