#pragma once

#include "Component.h"
#include "Vec.h"

class TimerJumper : public Component
{
private:
	Vec3f targetPosition;
	Vec3f targetPosition2;
	bool target1 = false;
	float timer = 1;
public:
	TimerJumper(const Vec3f &targetPosition, const Vec3f &targetPosition2);
	~TimerJumper();

	void update(float elapsedTime) override;
};

