#pragma once
#include "mge/core/Component.h"

class KeyMoveComponent : public Component
{

private:
	float m_moveSpeed = 5;
	float m_turnSpeed = 10;

public:
	KeyMoveComponent();
	virtual ~KeyMoveComponent();

	void Update(float timeStep) override;
};

