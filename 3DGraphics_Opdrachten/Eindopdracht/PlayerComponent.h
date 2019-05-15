#pragma once

#include "Component.h"

// Player component to control player.
class PlayerComponent : public Component
{
private:
	float speed = 5;
	void move(float angle, float fac);
public:
	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

