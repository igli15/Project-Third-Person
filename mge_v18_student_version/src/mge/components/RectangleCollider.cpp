#include "RectangleCollider.h"



RectangleCollider::RectangleCollider()
{
}


RectangleCollider::~RectangleCollider()
{
}

void RectangleCollider::DetectCollision()
{
}

bool RectangleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

bool RectangleCollider::IsColliding(CircleCollider * sphereCollider)
{
	std::cout << "NO REC-CIRCLE COLLISION" << std::endl;
	return false;
}

bool RectangleCollider::IsColliding(RectangleCollider * rectangleCollider)
{

	return false;
}
