#include "CircleCollider.h"

void CircleCollider::Start()
{

}

void CircleCollider::Update(float timeSteps)
{
	//ColliderComponent::Update(timeSteps);
	//Collider update =>  save old position
	//Sphere   update =>  Check if colliding
	DetectCollision();
}

glm::vec2 CircleCollider::GetWorld2Dposition()
{
	//Removing y positiong from gameObject position
	glm::vec3 pos3d=m_gameObject->transform->WorldPosition();

	return glm::vec2(pos3d.x, pos3d.z);
}

void CircleCollider::DetectCollision()
{
	bool isColliding=AbstractGame::Instance()->GetCollisionManager()->CheckCollisionInWorld(this);
	if (isColliding)
	{
		std::cout << "COLLISION" << std::endl;
	}
}

bool CircleCollider::IsColliding(ColliderComponent * collider)
{
	//Redispatching...
	return collider->IsColliding(this);
}

bool CircleCollider::IsColliding(CircleCollider * otherCollider)
{
	glm::vec2 distance = otherCollider->GetWorld2Dposition() - GetWorld2Dposition();
	float length = glm::length(distance);
	return (length <= otherCollider->radius + radius);
}


