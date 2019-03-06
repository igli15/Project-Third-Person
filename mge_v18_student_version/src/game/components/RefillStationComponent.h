#pragma once
#include "mge/core/Component.h"

class RefillStationComponent :public Component
{
public:
	void Start();
	void Update();
	void OnTrigger(CollisionInfo* collisionInfo);

	RefillStationComponent();
	virtual ~RefillStationComponent();
};

