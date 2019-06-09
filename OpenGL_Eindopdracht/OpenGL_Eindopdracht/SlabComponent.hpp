#pragma once
#include "DrawComponent.h"
#include <GL\freeglut.h>

class SlabComponent : public DrawComponent
{
public:
	SlabComponent(float size, GLuint textureID)
		: size(size), textureID(textureID) {}
	~SlabComponent() {}

	virtual void draw() override;
private:
	float size;
	GLuint textureID;
};