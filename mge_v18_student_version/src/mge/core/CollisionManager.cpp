#include "CollisionManager.h"

int CollisionManager::AddCollider(ColliderComponent * newCollider)
{
	std::cout << "Add collider" << std::endl;
	m_colliders.push_back(newCollider);
	return m_colliders.size();
}

bool CollisionManager::CheckCollisionInWorld(ColliderComponent * targetCollider)
{
	std::vector<std::string> filters = targetCollider->GetCollisionFilterTags();

	if (filters.size() == 0) return false;

	for (int colliderIndex = m_colliders.size() - 1; colliderIndex >= 0; --colliderIndex)
	{
		for (int i = 0; i < filters.size(); i++)
		{
			if (m_colliders[colliderIndex]->GetCollisionLayerTag() == filters[i]  && 
				targetCollider->GetGameObject()->ID() != m_colliders[colliderIndex]->GetGameObject()->ID())
			{

				if (targetCollider->IsColliding(m_colliders[colliderIndex]))
				{
					return true;
				}
			}
			
		}

	}
	return false;
}
