#include "cube.h"
#include <iostream>

Cube::Cube(float scale, Vector3 translation)
	: WorldObject(scale)
{
	this->translation = translation;	
}

void Cube::SetColor(float r, float g, float b)
{
	for (int i = 0; i < SIDES; i++)
		SetColorSide(i, r, g, b);
}

void Cube::SetColorSide(int side, float r, float g, float b)
{
	sides[side][0] = r;
	sides[side][1] = g;
	sides[side][2] = b;
}

void Cube::Update(float deltaTime)
{
	//rotation.x += 16.5f * deltaTime;
	//rotation.y += 22.5f * deltaTime;
}
float worldScale = 1.0f;
void Cube::Draw()
{
	// Start matrix
	glPushMatrix();

	// Schaal met wereld schaal
	glTranslatef(translation.x * worldScale, translation.y * worldScale, translation.z * worldScale);
	
	// Roteer assen op hoek
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
	
	// Schaal object
	glScalef(scale * worldScale, scale * worldScale, scale * worldScale);

	// Transleer opnieuw naar 0
	glTranslatef(0, 0, 0);

	DrawCube();

	glPopMatrix();
}

void Cube::DrawCube()
{
	// Voorkant
	glBegin(GL_QUADS);
	
	glColor3f(sides[0][0], sides[0][1], sides[0][2]);

	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	glEnd();

	// Achterkant
	glBegin(GL_QUADS);
	glColor3f(sides[1][0], sides[1][1], sides[1][2]);

	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Rechterkant
	glBegin(GL_QUADS);
	glColor3f(sides[2][0], sides[2][1], sides[2][2]);

	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Linkerkant
	glBegin(GL_QUADS);
	glColor3f(sides[3][0], sides[3][1], sides[3][2]);

	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Bovenkant
	glBegin(GL_QUADS);
	glColor3f(sides[4][0], sides[4][1], sides[4][2]);

	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Onderkant
	glBegin(GL_QUADS);
	glColor3f(sides[5][0], sides[5][1], sides[5][2]);

	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}
