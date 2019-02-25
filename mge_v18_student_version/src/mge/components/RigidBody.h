#pragma once
#include "../core/Component.h"
#include "../core/CollisionInfo.h"
#include "ColliderComponent.hpp"
#include "glm.hpp"
#include "../core/GameObject.hpp"
#include "Transform.h"
class RigidBody : public Component
{
public:
	glm::vec2 velocity;
	float bounciness = 1;
	RigidBody();
	virtual ~RigidBody();

	void Start();
	void Update(float timeStep);

	void SetCollider(ColliderComponent* collider);
	ColliderComponent* GetCollider();
	void OnCollisionStay(CollisionInfo* collisionInfo);
private:
	ColliderComponent* m_collider;
	Transform* m_transform;
	glm::vec3 m_oldPos;

};

