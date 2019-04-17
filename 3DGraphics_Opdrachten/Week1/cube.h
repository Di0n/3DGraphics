#pragma once
#include "world_object.h"

#define SIDES 6

class Cube :
	public WorldObject
{
public:
	Cube(float scale, Vector3 translation);
	~Cube() {};
	
	void SetColor(float r, float g, float b);
	void SetColorSide(int side, float r, float g, float b);


	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	void DrawCube();
	float r, g, b = 0;
	float sides[SIDES][3] = 
	{ 
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }, 
		{ 0,0,0 } 
	};
};

