#pragma once
#include <GL\freeglut.h>
class TextureManager;
struct Camera;
class Menu
{
public:
	enum Screen
	{
		DeadScreen = 1
	};
	Menu();
	~Menu();

	void init(TextureManager* m, Camera* cam);
	void setCurrentScreen(const Screen& scr);
	void draw();
	void update(float dt);
	int getCurrentIndex() const { return index; }
	void setIndex(int idx) { index = idx; }
private:
	int index;
	Screen currentScreen;
	TextureManager* textureManager;
	float size = 0.1f;
	Camera* cam;
};

