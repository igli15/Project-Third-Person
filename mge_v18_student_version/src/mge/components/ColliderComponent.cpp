#include "ColliderComponent.hpp"

void ColliderComponent::Awake()
{
	AbstractGame::Instance()->GetCollisionManager()->AddCollider(this);
	SetCollisionLayerTag("default");
}

void ColliderComponent::Update(float timeSteps)
{
	//Update
}

void ColliderComponent::SetCollisionLayerTag(std::string layerTag)
{
	m_collisionLayerTag= layerTag;
}

void ColliderComponent::AddCollisionFilterTag(std::string filterTag)
{
	m_collisionFilterTags.push_back(filterTag);
}

glm::vec2 ColliderComponent::GetWorld2Dposition()
{
	//Removing y positiong from gameObject position
	glm::vec3 pos3d = m_gameObject->transform->WorldPosition();

	return glm::vec2(pos3d.x, pos3d.z);
}
