#include <GL\freeglut.h>
#include <GL\GLU.h>
#include <iostream>
#include <vector>
#include <memory>
#include <windows.h>
#include <ctime>
#include "world_object.h"
#include "cube.h"

void onDisplay();
void onReshape(int newWidth, int newHeight);
void onKeyboard(unsigned char key, int mouseX, int mouseY);
void onUpdate();
void onMouse(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void onSpecialFunc(int key, int x, int y);

#define WIDTH	1920
#define HEIGHT	1080
#define ESCAPE_KEY 27

using std::vector;
using std::unique_ptr;

typedef unique_ptr<WorldObject> WorldObject_Ptr; // shared_ptr

vector <WorldObject_Ptr> objectList;

bool init()
{
	srand(static_cast<unsigned>(time(0)));

	Vector3 pos1;
	pos1.x = 0;
	pos1.y = 0;
	pos1.z = 0;
	Vector3 pos2;
	pos2.x = 2;
	pos2.y = 0;
	pos2.z = 0;
	Vector3 pos3;
	pos3.x = -2;
	pos3.y = 0;
	pos3.z = 0;
	Vector3 pos4;
	pos4.x = 0;
	pos4.y = 0;
	pos4.z = 2;
	
	Cube* cube1 = new Cube(1, pos1);
	cube1->SetColor(1.0f, 0.0f, 0.0f);
	objectList.push_back(unique_ptr<Cube>(cube1));
	Cube* cube2 = new Cube(1, pos2);
	cube2->SetColor(0.5f, 0.8f, 1.0f);
	objectList.push_back(unique_ptr<Cube>(cube2));
	objectList.push_back(unique_ptr<Cube>(new Cube(1, pos3)));
	objectList.push_back(unique_ptr<Cube>(new Cube(1, pos4)));


	return true;
}

void cleanUp()
{
	objectList.clear();
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutCreateWindow("Week 1 Kubus");
	glutDisplayFunc(onDisplay);
	glutKeyboardFunc(onKeyboard);
	glutIdleFunc(onUpdate);
	glutSpecialFunc(onSpecialFunc);
	glutMotionFunc(onMouseMove);
	// Achtergrond
	//glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	
	init();
	
	glutMainLoop();

	cleanUp();
	return 0;
}

void onDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, WIDTH / (float) HEIGHT, 0.1f, 50.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 3, -5,
				0, 0, 0,
				0, 1, 0);

	for (auto& obj : objectList) obj->Draw();

	glFlush();
	glutSwapBuffers();
}

void onKeyboard(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
		case ESCAPE_KEY:
			exit(1);
		break;
		default:
			break;
	}
}

int prevTime = 0;
int animationTime = 0;
void onUpdate()
{
	Sleep(1);

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME); // in millis 
	float deltaTime = ((float)(timeSinceStart - prevTime)) / 1000;
	
	int i = 0;
	for (auto & obj : objectList)
	{
		Vector3 vec = obj->GetRotation();
		if (i == 0) vec.x += 22 * deltaTime;
		else if (i == 1) vec.y += 22 * deltaTime;
		else if (i == 2) vec.z += 22 * deltaTime;
		else if (i == 3) vec.y += 22 * deltaTime;

		obj->SetRotation(vec);
		obj->Update(deltaTime);
		i++;
	}
	prevTime = timeSinceStart;
	glutPostRedisplay();
}


void onSpecialFunc(int key, int x, int y)
{
	WorldObject* wo = objectList[0].get();

	Vector3 rotation = wo->GetRotation();
	switch (key)
	{
	case GLUT_KEY_UP:
		//rotateX += 5;
		rotation.x += 5;
		wo->SetRotation(rotation);
		break;
	case GLUT_KEY_DOWN:
		//rotateX -= 5;
		rotation.x -= 5;
		wo->SetRotation(rotation);
		//wo->SetRotation(rotation);
		break;
	case GLUT_KEY_LEFT:
		rotation.y -= 5;
		wo->SetRotation(rotation);
		//wo->SetRotation(rotation);
		//rotateY -= 5;
		break;
	case GLUT_KEY_RIGHT:
		//rotateY += 5;
		rotation.y += 5;
		wo->SetRotation(rotation);
		//wo->SetRotation(rotation);
		break;
	case GLUT_KEY_F8:
	{
		Cube* cube = static_cast<Cube*>(wo);
		cube->SetColorSide(1, 1.0f, 0.2f, 1.0f);

		break;
	}
	default:
		break;
	}

	glutPostRedisplay();
}

void onMouseMove(int x, int y)
{
	if (objectList.size() < 3) return;
	Cube* cube = static_cast<Cube*>(objectList[3].get());
	if (cube == nullptr)
		return;

	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	cube->SetColor(r, r, b);
}