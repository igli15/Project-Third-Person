#pragma once
#include "mge/core/Component.h"

class RefillStationComponent :public Component
{
public:
	void Start();
	void Update();

	RefillStationComponent();
	virtual ~RefillStationComponent();
};

