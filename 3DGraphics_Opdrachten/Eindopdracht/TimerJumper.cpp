#include "TimerJumper.h"
#include "GameObject.h"
#include "MoveToComponent.h"



TimerJumper::TimerJumper(const Vec3f &targetPosition, const Vec3f &targetPosition2) : targetPosition(targetPosition), targetPosition2(targetPosition2)
{
}


TimerJumper::~TimerJumper()
{
}

void TimerJumper::update(float elapsedTime)
{
	auto moveTo = gameObject->getComponent<MoveToComponent>();

	timer -= elapsedTime;
	if (timer <= 0)
	{
		timer = 5;
		if (target1)
		{
			moveTo->target = targetPosition;
	//		moveTo->speed = 0.025f;
		}
		else
		{
			moveTo->target = targetPosition2;
	//		moveTo->speed = 0.05f;
		}
		target1 = !target1;

	}
}
