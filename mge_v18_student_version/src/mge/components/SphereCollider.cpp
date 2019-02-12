#include "SphereCollider.h"

void SphereCollider::Update(float timeSteps)
{
	//ColliderComponent::Update(timeSteps);
	//Collider update =>  save old position
	//Sphere   update =>  Check if colliding

	DetectCollision();
}

glm::vec2 SphereCollider::GetWorld2Dposition()
{
	//Removing y positiong from gameObject position
	glm::vec3 pos3d=m_gameObject->transform->WorldPosition();

	return glm::vec2(pos3d.x, pos3d.z);
}

void SphereCollider::DetectCollision()
{
	bool isColliding=AbstractGame::Instance()->GetCollisionManager()->CheckCollisionInWorld(this);
	if (isColliding)
	{
		std::cout << "COLLISION" << std::endl;
	}
}

bool SphereCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

bool SphereCollider::IsColliding(SphereCollider * otherCollider)
{
	glm::vec2 distance = otherCollider->GetWorld2Dposition() - GetWorld2Dposition();
	float length = glm::length(distance);
	return (length <= otherCollider->radius + radius);
}


