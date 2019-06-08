#pragma once
#include <vector>
class GameObject;
struct Camera;
class TextureManager;
class Level
{
public:
	Level(Camera* camera, std::vector<GameObject*>* objects, TextureManager* textureManager) 
		:  camera(camera), objects(objects), textureManager(textureManager) {}
	~Level() {};

	void setup();
private:
	std::vector<GameObject*>* objects;
	Camera* camera;
	TextureManager* textureManager;
	void setupWalls();
	void setupFloor();

};