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
	glm::vec2 GetWorld2Dposition();

	bool IsColliding(ColliderComponent * collider);

	bool IsColliding(CircleCollider* otherCollider); //Sphere - Sphere

protected:
	glm::vec2 m_oldPos;

	// Inherited via ColliderComponent
	void DetectCollision();


};
