#pragma once

#include "DrawComponent.h"

#include <GL\freeglut.h>
// A cube (so drawable and updateable)
class WallComponent : public DrawComponent
{
private:
	float size;
	GLuint textureID;
public:
	WallComponent(float size, GLuint textureID) : size(size), textureID(textureID) {}
	~WallComponent();

	virtual void draw() override;
};

