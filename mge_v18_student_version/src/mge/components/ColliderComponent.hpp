#pragma once
#include "../core/Component.h"
#include "../core/GameObject.hpp"

class ColliderComponent : public Component
{
public:
	void Awake() override;
	void Update(float timeSteps) override;
};