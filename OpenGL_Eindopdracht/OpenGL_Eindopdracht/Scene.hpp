#pragma once
#include <vector>
class GameObject;
struct Camera;
class TextureManager;

typedef std::vector<GameObject*> ObjectList;
class Scene
{
public:
	Scene(Camera* camera, ObjectList* objects, TextureManager* textureManager)
		: camera(camera), objects(objects), textureManager(textureManager) {}
	~Scene() {}

	void setup();
private:
	Camera* camera;
	ObjectList* objects;
	TextureManager* textureManager;

	void setupWalls();
	void setupFloor();
	void setupCeiling();
};