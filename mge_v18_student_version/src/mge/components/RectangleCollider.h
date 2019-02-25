#pragma once
#include "ColliderComponent.hpp"

class ColliderComponent;

class RectangleCollider :public ColliderComponent
{
public:
	float width = 2;
	float height = 2;
	
	int i = 0;

	virtual ~RectangleCollider();

	void Update(float timeSteps);
	// Inherited via ColliderComponent
	void DetectCollision();

	CollisionInfo* IsColliding(ColliderComponent * collider);

	CollisionInfo* IsColliding(CircleCollider * circleCollider);
	CollisionInfo* IsColliding(RectangleCollider * rectangleCollider);

};

