#pragma once
#include "mge/core/Component.h"
#include "mge/components/RigidBody.h"

class PlayerMovementComponent :public Component
{
public:

	void Awake();
	void Start();
	void Update(float timeStep);

	void SetPlayerNumber(int playerNumber);

	PlayerMovementComponent();
	virtual ~PlayerMovementComponent();
private:
	RigidBody* m_rigidbody;
	int m_playerNumber;
};

