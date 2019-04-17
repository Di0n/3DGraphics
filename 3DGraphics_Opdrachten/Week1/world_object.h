#pragma once

#include <GL\freeglut.h>
#include <GL\GLU.h>
#include "globals.h"
class WorldObject
{
public:
	WorldObject(float scale);
	virtual ~WorldObject() {};
	
	Vector3			GetRotation() const;
	Vector3			GetTranslation() const;
	void			SetTranslation(Vector3 vec);
	void			SetRotation(Vector3 rot);

	virtual void	Update(float deltaTime) = 0;
	virtual void	Draw() = 0;

protected: 
	// Transform
	Vector3 translation;
	Vector3 rotation;
	float scale = 0;
};

