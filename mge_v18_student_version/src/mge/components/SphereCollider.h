#pragma once
#include "ColliderComponent.hpp"
#include <glm.hpp>

class ColliderComponent;

class SphereCollider :public ColliderComponent
{
public:
	float radius = 1.0f;

	void Update(float timeSteps);
	glm::vec2 GetWorld2Dposition();

	bool IsColliding(ColliderComponent * collider);

	bool IsColliding(SphereCollider* otherCollider); //Sphere - Sphere

protected:
	glm::vec2 m_oldPos;

	// Inherited via ColliderComponent
	void DetectCollision();


};
