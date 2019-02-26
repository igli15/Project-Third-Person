#pragma once
#include "../core/XMLComponent.h"
#include "../core/CollisionInfo.h"
#include "ColliderComponent.hpp"
#include "glm.hpp"
#include "../core/GameObject.hpp"
#include "../components/Transform.h"

class RigidBody : public XMLComponent
{
public:
	glm::vec2 velocity;
	
	RigidBody();
	virtual ~RigidBody();

	void Start();
	void Update(float timeStep);

	void SetCollider(ColliderComponent* collider);
	ColliderComponent* GetCollider();
	void OnCollisionStay(CollisionInfo* collisionInfo);

	void SetAcceleration(glm::vec2 a);
	void SetMaxSpeed(float maxSpeed);

	glm::vec2 GetAcceleration();
	float GetMaxSpeed();

	void Parse(rapidxml::xml_node<>* compNode) override;

private:
	ColliderComponent* m_collider;
	Transform* m_transform;


	glm::vec3 m_oldPos;
	glm::vec2 m_acceleration;
	float m_maxSpeed = 3;
	float m_friction = 0;
	float bounciness = 0.1f;
};

