#pragma once

#include "Component.h"

// Player component to control player.
class PlayerComponent : public Component
{
	float speed = 5;
public:
	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

