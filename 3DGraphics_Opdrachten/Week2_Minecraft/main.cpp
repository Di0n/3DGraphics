#include <GL/freeglut.h>
#include <cstdio>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define COLUMNS 16

float lastFrameTime = 0;

int width, height;
GLuint textureId;
int textureWidth, textureHeight;
int sky[20][20][10] = {-1};

//{
//	{ {10 items}, {10 items}, {10 items} x 20 }
//	{ {10 items}, { 10 items }, { 10 items } x 20 }
//	x20
//}
struct Camera
{
	float posX = 0;
	float posY = -4;
	float rotX = 0;
	float rotY = 0;
} camera;

bool keys[255];


void drawCube()
{
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);

	glColor3f(1, 1, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);

	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	glColor3f(0, 1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();
}

void drawTexCube()
{
	//glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);

	glTexCoord2f(0, 0); glVertex3f(-1, -1 , 1);
	glTexCoord2f(0, 1); glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, 1, 1);

	glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);

	glTexCoord2f(0, 0);  glVertex3f(1, -1, -1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1,1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, 1);

	glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);

	glTexCoord2f(0, 0); glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, 1, 1);

	glEnd();
}
//int spriteWidth = 16, spriteHeight = 16;
//int texWidth = TILE_SIZE, texHeight = TILE_SIZE;


// widht & height % 16 voor grootte in 0,1 formaat

void drawCube(int index)
{
	/*
	In het geval van 3
	row = 3 / 16 = 0.1875 = 0 = Rij 1
	column = 3 % 16 = 3 Item = 3
	*/
	const int row = index / COLUMNS;
	const int column = index % COLUMNS;
	const float textureSize = (float)1 / COLUMNS;//0.0625f;//(textureWidth / COLUMNS) % COLUMNS;

	//float div = index / 255;
	//float x1 = index * div;
	//float x2 = (index * div) + div;

	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_QUADS);

	float x = column * textureSize;
	float y = row * textureSize;
	
	float xEnd = x + textureSize;
	float yEnd = y + textureSize;


	// Achterkant
	// Original
	//glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	//glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
	//glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	//glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);

	glTexCoord2f(x, y); glVertex3f(1, 1, -1);
	glTexCoord2f(xEnd, y); glVertex3f(-1, 1, -1);
	glTexCoord2f(xEnd, yEnd); glVertex3f(-1, -1, -1);
	glTexCoord2f(x, yEnd); glVertex3f(1, -1, -1);


	// Voorkant
	//
	glTexCoord2f(x, y); glVertex3f(-1, 1, 1);
	glTexCoord2f(x + textureSize, y); glVertex3f(1, 1, 1);
	glTexCoord2f(x + textureSize, y + textureSize); glVertex3f(1, -1, 1);
	glTexCoord2f(x, y + textureSize); glVertex3f(-1, -1, 1);

	// Original
	/*glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, 1, 1);*/

	// Zijkant links
	// Original
	/*glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);*/

	glTexCoord2f(x, y); glVertex3f(-1, 1, -1);
	glTexCoord2f(x, y + textureSize); glVertex3f(-1, -1, -1);
	glTexCoord2f(x + textureSize, y + textureSize); glVertex3f(-1, -1, 1);
	glTexCoord2f(x + textureSize,y); glVertex3f(-1, 1, 1);

	// Zijkant rechts
	// Original
	//glTexCoord2f(0, 0);  glVertex3f(1, -1, -1);
	//glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
	//glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	//glTexCoord2f(1, 0); glVertex3f(1, -1, 1);

	glTexCoord2f(x, y);  glVertex3f(1, 1, 1);
	glTexCoord2f(x, y + textureSize); glVertex3f(1, -1, 1);
	glTexCoord2f(x + textureSize, y + textureSize); glVertex3f(1, -1, -1);
	glTexCoord2f(x + textureSize, y); glVertex3f(1, 1, -1);

	// Onderkant
	// Original
	/*glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);*/
	glTexCoord2f(x, y); glVertex3f(-1, -1, -1);
	glTexCoord2f(x, y + textureSize); glVertex3f(1, -1, -1);
	glTexCoord2f(x + textureSize, y + textureSize); glVertex3f(1, -1, 1);
	glTexCoord2f(x + textureSize, y); glVertex3f(-1, -1, 1);

	// Bovenkant
	// Original
	/*glTexCoord2f(0, 0); glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, 1, 1);*/

	glTexCoord2f(x, y); glVertex3f(-1, 1, -1);
	glTexCoord2f(x, y + textureSize); glVertex3f(1, 1, -1);
	glTexCoord2f(x + textureSize, y + textureSize); glVertex3f(1, 1, 1);
	glTexCoord2f(x + textureSize, y); glVertex3f(-1, 1, 1);

	glEnd();
}

void display()
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / height, 0.1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, 0, camera.posY);
	
	glBegin(GL_QUADS);
	glColor3f(0.1f, 1.0f, 0.2f);
	glVertex3f(-15, -1, -15);
	glVertex3f(15, -1, -15);
	glVertex3f(15, -1, 15);
	glVertex3f(-15, -1, 15);
	glEnd();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.0f, 0);
	drawCube(24);
	glPopMatrix();
	/*for (int x = -10; x <= 10; x += 5)
	{
		for (int y = -10; y <= 10; y += 5)
		{
			glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef((float)x, 0.0f, (float)y);
			drawCube(24);
			glPopMatrix();
		}
	}*/

	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);

	glutPostRedisplay();
}

bool justMovedMouse = false;
void mousePassiveMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
	}
	if (!justMovedMouse)
	{
		glutWarpPointer(width / 2, height / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	keys[key] = true;
}

void keyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}
void initGraphics()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.5);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	/*unsigned char data[32 * 32 * 4];
	for (int i = 0; i < 32 * 32 * 4; i++)
	{
		data[i] = rand() % 256;
	}*/

	int bpp;
	//stbi_set_flip_vertically_on_load(1);

	unsigned char* imgData = stbi_load("terrain.png", &textureWidth, &textureHeight, &bpp, 4);
	glTexImage2D(GL_TEXTURE_2D, 
				0, 
				GL_RGBA,
				textureWidth,
				textureHeight,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				imgData);
	stbi_image_free(imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}
int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInit(&argc, argv);
	glutCreateWindow("Hello World");

	memset(keys, 0, sizeof(keys));
	srand(time(NULL));
	

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(width / 2, height / 2);
	initGraphics();
	
	glutMainLoop();


	return 0;
}