#pragma once

#include "Component.h"
#include "Vec.h"
// Player component to control player.
struct Camera;
class CameraComponent;
class PlayerComponent : public Component
{
private:
	const Vec3f GRAVITY			= Vec3f(0.0f, -9.81f, 0.0f);
	const float FRICTION		= 0.98f;
	const float JUMP_VELOCITY	= 4.0f;
	const float MIN_HEIGHT_MOVE = 0.02f;
	const float ANGLE_W			= 90;
	const float ANGLE_A			= 0;
	const float ANGLE_S			= 270;
	const float ANGLE_D			= 180;

	float speed = 50;//50;
	float runSpeed = 90;//90;

	void move(Camera* cam, float angle, float speed);
	void handleInput(float elapsedTime, Camera* cam);
public:
	PlayerComponent();
	~PlayerComponent();

	virtual void update(float elapsedTime) override;
};

