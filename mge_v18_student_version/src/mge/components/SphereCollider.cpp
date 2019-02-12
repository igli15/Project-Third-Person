#include "SphereCollider.h"

void SphereCollider::Update(float timeSteps)
{
	ColliderComponent::Update(timeSteps);
	//Collider update =>  save old position
	//Sphere   update =>  Check if colliding
}

glm::vec2 SphereCollider::GetWorld2Dposition()
{
	//Removing y positiong from gameObject position
	glm::vec3 pos3d=m_gameObject->transform->WorldPosition;
	return glm::vec2(pos3d.x, pos3d.z);
}
