#pragma once
#include "../core/Component.h"
#include "../core/GameObject.hpp"
#include "../core/AbstractGame.hpp"
#include "../core/CollisionManager.h"
//#include "mge/components/SphereCollider.h"

class SphereCollider;

class ColliderComponent : public Component
{
public:
	void Awake() override;
	void Update(float timeSteps) override;

	virtual void DetectCollision() = 0;
	virtual bool IsColliding(ColliderComponent* collider) = 0; //Redispatching...

	virtual bool IsColliding(SphereCollider* sphereCollider) = 0; // Sphere
	int id = 0;
};