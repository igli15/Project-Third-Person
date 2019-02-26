#pragma once

#include "../mge/core/GameObject.hpp"
#include "components/PlayerMovementComponent.h"
#include "../mge/components/RigidBody.h"
#include "../mge/components/CircleCollider.h"

class Player :public GameObject
{
public:
	Player();
	~Player();

	void Load();
	void Start();

	void SetPlayerNumber(int playerNumber);
private:
	PlayerMovementComponent* m_movementComponent;
	RigidBody* m_rigidBody;
	CircleCollider* m_circleCollider;
	MeshRenderer* m_meshRenderer;
};

