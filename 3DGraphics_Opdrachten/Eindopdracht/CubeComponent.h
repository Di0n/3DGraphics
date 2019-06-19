#pragma once

#include "DrawComponent.h"

// A cube (so drawable and updateable)
class CubeComponent : public DrawComponent
{
	float size;
public:
	CubeComponent(float size);
	~CubeComponent();

	virtual void draw() override;
};

