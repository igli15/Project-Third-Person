#pragma once
#include "ColliderComponent.hpp"
#include <glm.hpp>

class ColliderComponent;
class RectangleCollider;

class CircleCollider :public ColliderComponent
{
public:
	float radius = 1.0f;
	void Start();
	void Update(float timeSteps);


	CollisionInfo* IsColliding(ColliderComponent * collider);

	CollisionInfo* IsColliding(CircleCollider* otherCollider); //Circle - Circle
	CollisionInfo* IsColliding(RectangleCollider * rectangleCollider); //Circle - Rectangle
	glm::vec2 m_oldPos;

	void DetectCollision();



	// Inherited via ColliderComponent


};
