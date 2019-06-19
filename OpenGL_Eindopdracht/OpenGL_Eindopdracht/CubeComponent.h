#pragma once

#include "DrawComponent.h"
#include <GL/freeglut.h>
// A cube (so drawable and updateable)
class CubeComponent : public DrawComponent
{
	float size;
	GLuint textureID;
public:
	CubeComponent(float size, GLuint textureID);
	~CubeComponent();

	virtual void draw() override;
};

