#pragma once
#include <list>
class GameObject;
struct Camera;
class TextureManager;
class Level
{
public:
	Level(Camera* camera, std::list<GameObject*>* objects, TextureManager* textureManager) 
		:  camera(camera), objects(objects), textureManager(textureManager) {}
	~Level() {};

	void setup();
private:
	std::list<GameObject*>* objects;
	Camera* camera;
	TextureManager* textureManager;
	void setupWalls();
	void setupFloor();

};