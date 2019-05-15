#pragma once

#include "DrawComponent.h"

class BackgroundComponent : public DrawComponent
{
public:
	BackgroundComponent();
	~BackgroundComponent();

	virtual void draw() override;
};

