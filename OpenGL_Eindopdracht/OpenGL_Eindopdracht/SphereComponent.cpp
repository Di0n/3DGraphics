#include "SphereComponent.hpp"

void SphereComponent::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);
	//glColor3f(0.8f, 0.2f, 0.1f);
	//glutSolidSphere(1.0, 20, 50);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, size, 20, 20);
	glDisable(GL_TEXTURE_2D);

}