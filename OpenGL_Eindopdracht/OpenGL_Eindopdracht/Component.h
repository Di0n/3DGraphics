#pragma once
class GameObject;
// A non drawable component
class Component
{
protected:
	GameObject* gameObject;

public:
	Component();
	virtual ~Component();

	virtual void update(float elapsedTime) {};

	inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};

