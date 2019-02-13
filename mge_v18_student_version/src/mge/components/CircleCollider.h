#pragma once
#include "ColliderComponent.hpp"
#include <glm.hpp>

class ColliderComponent;

class CircleCollider :public ColliderComponent
{
public:
	float radius = 1.0f;
	void Start();
	void Update(float timeSteps);


	bool IsColliding(ColliderComponent * collider);

	bool IsColliding(CircleCollider* otherCollider); //Circle - Circle
	bool IsColliding(RectangleCollider * rectangleCollider); //Circle - Rectangle
	glm::vec2 m_oldPos;

	void DetectCollision();



	// Inherited via ColliderComponent


};
