#pragma once

#include "Component.h"

// Object spinner.
class SpinComponent : public Component
{
	float speed;
public:
	SpinComponent(float speed);
	~SpinComponent();

	virtual void update(float elapsedTime) override;
};

