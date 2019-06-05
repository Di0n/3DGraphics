#pragma once

#include "Component.h"

// Drawable component
class DrawComponent : public Component
{
public:
	DrawComponent();
	virtual ~DrawComponent();
	virtual void draw() = 0;
};

