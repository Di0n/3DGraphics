/*
	Engine functionality
*/
#include <iostream>
#include <GL\freeglut.h>
#include "Game.hpp"

// Status codes
#define GLUT_INIT_FAILED 1
#define OPENGL_INIT_FAILED 2

#define APP_NAME "Game"
#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1440


int windowWidth;
int windowHeight;

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{
	Game::onKey(key);
}

void keyboardup(unsigned char key, int x, int y)
{
	Game::onKeyUp(key);
}

void mousePassiveMotion(int x, int y)
{
	Game::onMouseMove(x, y);
}

void display()
{
	glClearColor(52.0f /255.0f, 80.0f /255.0f, 92.0f/255.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, windowWidth / (float)windowHeight, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Game::draw();

	glutSwapBuffers();
}

int lastTime = 0;
void idle()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	Game::update(deltaTime);
	// update

	glutPostRedisplay();
}

bool initGlut(int argc, char** argv)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInit(&argc, argv);
	glutCreateWindow(APP_NAME);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardup);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutFullScreen();

	return true;
}

bool initOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.5);

	return true;
}
int main(int argc, char** argv)
{
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;

	if (initGlut(argc, argv))
		std::cout << "Succesfully initialized glut.\n";
	else
	{
		std::cout << "Failed initializing glut.\n";
		return GLUT_INIT_FAILED;
	}

	if (initOpenGL())
		std::cout << "Succesfully initialized OpenGL.\n";
	else
	{
		std::cout << "Failed initializing OpenGL.\n";
		return OPENGL_INIT_FAILED;
	}

	Game::onResize(windowWidth, windowHeight);

	// Start loading in game content.
	Game::loadContent();

	// Start game.
	glutMainLoop();

	Game::onClose();

	return EXIT_SUCCESS;
}