#pragma once
#include "DrawComponent.h"
#include <GL\freeglut.h>

class FloorComponent : public DrawComponent
{
public:
	FloorComponent(float size, GLuint textureID) : size(size), textureID(textureID) {}
	~FloorComponent() {}

private:
	float size;
	GLuint textureID;

	virtual void draw() override;
};