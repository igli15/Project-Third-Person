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
	//if (filters.size() == 0) return;
	for (int colliderIndex = m_colliders.size() - 1; colliderIndex >= 0; --colliderIndex)
	{
		//if its not me and I am colliding with other object

		
		for (int i = 0; i < filters.size(); i++)
		{
			if (m_colliders[colliderIndex]->GetCollisionLayerTag() == filters[i])
			{
				
				if (targetCollider->GetGameObject()->ID() != m_colliders[i]->GetGameObject()->ID() &&
					targetCollider->IsColliding(m_colliders[i]))
				{
					std::cout << "filter: " << filters[i] << " " << "layer: " << m_colliders[colliderIndex]->GetCollisionLayerTag() << std::endl;
					return true;
				}
			}
		}


	}
	return false;
}
