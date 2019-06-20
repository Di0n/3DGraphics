#pragma once
#include "DrawComponent.h"
#include <GL/freeglut.h>
// A cube (so drawable and updateable)
class StarComponent : public DrawComponent
{
	float size;
public:
	StarComponent(float size) : size(size) {}
	~StarComponent() {}

	virtual void draw() override;
};

