#pragma once
#include "mge/core/GameObject.hpp"
#include "mge/components//RigidBody.h"

class PhysicsTestObject :public GameObject
{
public:
	PhysicsTestObject();
	~PhysicsTestObject();

	void Load();
	void Start();
	void Update(float timeStep);

	void SetPlayer(float playerNumber);

	RigidBody* rigidbody;
	CircleCollider* circleCollider;
private:
	float m_playerNumber;
};

