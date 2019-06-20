#include "Menu.hpp"
#include "TextureManager.hpp"
#include "TextureResource.hpp"
#include "Camera.hpp"

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::init(TextureManager* m, Camera* cam)
{
	textureManager = m;
	this->cam = cam;
}

void Menu::update(float dt)
{

}

void Menu::setCurrentScreen(const Screen& scr)
{
	currentScreen = scr;
}
void Menu::draw()
{
	switch (currentScreen)
	{
	case Screen::DeadScreen:
	{
		const GLuint textureID = textureManager->getTexture(TEXTURE_DIED_SCREEN);

		glPushMatrix();
		glTranslatef(0, 0, -8);
		//glRotatef(cam->rotX, 1, 0, 0);
		//glRotatef(cam->rotY, 0, 1, 0);
		//glRotatef(cam->rotZ, 0, 0, 1);
		glScalef(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
		glTexCoord2f(0, 1); glVertex3f(-size, size, size);
		glTexCoord2f(1, 1); glVertex3f(size, size, size);
		glTexCoord2f(1, 0); glVertex3f(size, -size, size);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		break;
	}
	default:
		break;
	}
}
