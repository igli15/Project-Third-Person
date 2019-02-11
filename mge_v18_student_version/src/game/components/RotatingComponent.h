#pragma once
#include "../src/mge/core/Component.h"

class RotatingComponent :
	public Component
{
public:
	RotatingComponent();
	virtual ~RotatingComponent();

	void Update(float timeStep) override;
};

