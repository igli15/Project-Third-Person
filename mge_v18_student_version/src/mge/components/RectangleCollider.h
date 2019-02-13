#pragma once
#include "ColliderComponent.hpp"
class RectangleCollider :
	public ColliderComponent
{
public:
	RectangleCollider();
	virtual ~RectangleCollider();


	// Inherited via ColliderComponent
	virtual void DetectCollision() override;

	virtual bool IsColliding(ColliderComponent * collider) override;

	virtual bool IsColliding(CircleCollider * circleCollider) override;
	virtual bool IsColliding(RectangleCollider * rectangleCollider) override;

};

