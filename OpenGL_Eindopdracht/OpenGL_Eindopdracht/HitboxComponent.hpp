#pragma once
#include "Component.h"
#include "Vec.h"

class HitboxComponent : public Component
{
public:
	HitboxComponent(float sizeX, float sizeY, float sizeZ)
		: sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {}
	~HitboxComponent() {}

	float getSizeX() const
	{
		return sizeX;
	}
	float getSizeY() const
	{
		return sizeY;
	}
	float getSizeZ() const
	{
		return sizeZ;
	}

	bool collided(const HitboxComponent* hitbox) const;

	virtual void update(float elapsedTime) override;
private:
	float sizeX, sizeY, sizeZ;
};