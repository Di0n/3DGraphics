#pragma once
#include "DrawComponent.h"
#include <GL\freeglut.h>

class SphereComponent : public DrawComponent
{
public:
	SphereComponent(float size, GLuint textureID) : size(size), textureID(textureID)
	{
		sphere = gluNewQuadric();
	}
	~SphereComponent() 
	{
		if (sphere)
			gluDeleteQuadric(sphere);
	}

	virtual void draw() override;

private:
	float size;
	GLuint textureID;
	GLUquadricObj* sphere;
};