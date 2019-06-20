#include "StarComponent.hpp"




void StarComponent::draw()
{
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	 glVertex3f(-size, -size, -size);
	 glVertex3f(-size, -size, size);
	 glVertex3f(-size, size, size);
	 glVertex3f(-size, size, -size);

	 glColor3f(1, 1, 1);

	 glVertex3f(size, -size, -size);
	 glVertex3f(size, -size, size);
	 glVertex3f(size, size, size);
	 glVertex3f(size, size, -size);

	//glColor3f(0, 1, 0);
	 glColor3f(1, 1, 1);

	 glVertex3f(-size, -size, -size);
	 glVertex3f(-size, -size, size);
	 glVertex3f(size, -size, size);
	 glVertex3f(size, -size, -size);

	 glColor3f(1, 1, 1);

	 glVertex3f(-size, size, -size);
	 glVertex3f(-size, size, size);
	 glVertex3f(size, size, size);
	 glVertex3f(size, size, -size);

	//glColor3f(0, 0, 1);
	 glColor3f(1, 1, 1);

	 glVertex3f(-size, -size, -size);
	 glVertex3f(-size, size, -size);
	 glVertex3f(size, size, -size);
	 glVertex3f(size, -size, -size);
	 glColor3f(1, 1, 1);

	 glVertex3f(-size, -size, size);
	 glVertex3f(-size, size, size);
	 glVertex3f(size, size, size);
	 glVertex3f(size, -size, size);

	glEnd();
}
