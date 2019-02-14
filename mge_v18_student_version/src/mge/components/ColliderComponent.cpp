#include "ColliderComponent.hpp"

void ColliderComponent::Awake()
{
	AbstractGame::Instance()->GetCollisionManager()->AddCollider(this);
	SetCollisionLayerTag("default");
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
	if (m_collisionFilterTags.size() ==1 && m_collisionFilterTags[0]=="default")
	{
		//std::cout << "Removing default from filter tags" << std::endl;
		//m_collisionFilterTags.clear();
	}
	m_collisionFilterTags.push_back(filterTag);

	for (int i = 0; i < m_collisionFilterTags.size();  i++)
	{
		std::cout << "filter: " << m_collisionFilterTags[i] << std::endl;
	}
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
