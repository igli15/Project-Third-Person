#include "ColliderComponent.hpp"

void ColliderComponent::Awake()
{
	id=AbstractGame::Instance()->GetCollisionManager()->AddCollider(this);
}

void ColliderComponent::Update(float timeSteps)
{
	//Update
}

glm::vec2 ColliderComponent::GetWorld2Dposition()
{
	//Removing y positiong from gameObject position
	glm::vec3 pos3d = m_gameObject->transform->WorldPosition();

	return glm::vec2(pos3d.x, pos3d.z);
}
