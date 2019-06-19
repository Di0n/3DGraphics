#include "CubeComponent.h"



CubeComponent::CubeComponent(float size, GLuint textureID)
{
	this->size = size;
	this->textureID = textureID;
}


CubeComponent::~CubeComponent()
{
}

void CubeComponent::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	//glColor3f(1, 0, 0);
	glTexCoord2f(0,0); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, size, -size);

	glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);

	//glColor3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);

	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);

	//glColor3f(0, 0, 1);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);

	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glTexCoord2f(1,1); glVertex3f(size, size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
