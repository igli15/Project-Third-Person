#include "ColliderComponent.hpp"
#include "CircleCollider.h"
#include "RectangleCollider.h"

void ColliderComponent::Awake()
{
	AbstractGame::Instance()->GetCollisionManager()->AddCollider(this);
	

	//AddCollisionFilterTag("default");

}

void ColliderComponent::Update(float timeSteps)
{
	//Update
}

void ColliderComponent::SetCollisionLayerTag(std::string layerTag)
{
	m_collisionLayerTag= layerTag;
}

std::string ColliderComponent::GetCollisionLayerTag()
{
	return m_collisionLayerTag;
}

void ColliderComponent::AddCollisionFilterTag(std::string filterTag)
{
	m_collisionFilterTags.push_back(filterTag);
}

std::vector<std::string> ColliderComponent::GetCollisionFilterTags()
{
	return m_collisionFilterTags;
}

glm::vec2 ColliderComponent::GetWorld2Dposition()
{
	//Removing y positiong from gameObject position
	glm::vec3 pos3d = m_gameObject->transform->WorldPosition();

	return glm::vec2(pos3d.x, pos3d.z);
}

void ColliderComponent::SetTrigger(bool trigger)
{
	m_trigger = trigger;
}

bool ColliderComponent::IsTrigger()
{
	return m_trigger;
}

void ColliderComponent::Parse(rapidxml::xml_node<>* compNode)
{
}
