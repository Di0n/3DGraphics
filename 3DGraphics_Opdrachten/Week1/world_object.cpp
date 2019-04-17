#include "world_object.h"

WorldObject::WorldObject(float scale)
{
	this->scale = scale;
}

void WorldObject::SetRotation(Vector3 rot)
{
	this->rotation = rot;
}
Vector3 WorldObject::GetRotation() const
{
	return rotation;
}
void WorldObject::SetTranslation(Vector3 vec)
{
	this->translation = vec;
}
Vector3 WorldObject::GetTranslation() const
{
	return translation;
}