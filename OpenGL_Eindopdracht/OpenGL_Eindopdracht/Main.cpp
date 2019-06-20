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
#define FULLSCREEN


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
	//glClearColor(52.0f /255.0f, 80.0f /255.0f, 92.0f/255.0f, 1);
	glClearColor(0, 0, 0, 0);

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
#ifdef FULLSCREEN
	glutFullScreen();
#endif // FULLSCREEN
	return true;
}

bool initOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.5);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//GLfloat light_position[] = { -6.0, 0.0, 0.0, 1 };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	//GLfloat light_amb[] = { 0.0, 0.0, 0.0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	return true;


//	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat mat_shininess[] = { 50.0 };
//	GLfloat light_position[] = { 15.0, 3.0, 1.0, 0.0 };
//
////	GLfloat light_position[] = { 15.0f, 6.0, 3.0, 0.0 };
//	//glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_SMOOTH);
//
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//
//	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
//	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	/*glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);

	GLfloat ambient[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat position[] = { 0.0f,3.0f,3.0f,0.0f };
	GLfloat lightmodel[] = { 0.2f,0.2f,0.2f,1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightmodel);

	glEnable(GL_LIGHT1);

	GLfloat lightZeroPosition[] = { 10.0f,4.0f,10.0f,1.0f };
	GLfloat lightZeroColor[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);

	glEnable(GL_LIGHT0);*/


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