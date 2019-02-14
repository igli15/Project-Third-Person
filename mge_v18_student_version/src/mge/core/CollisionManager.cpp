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
			//std::cout << "seaarching for filter :" << filters[i]<<"/ "<< m_colliders[colliderIndex]->GetCollisionLayerTag() << std::endl;

			if (m_colliders[colliderIndex]->GetCollisionLayerTag() == filters[i])
			{
				//std::cout << "filter: " << filters[i] << " " << "layer: " << m_colliders[colliderIndex]->GetCollisionLayerTag() << std::endl;
				//std::cout << "Objects are: " << targetCollider->GetGameObject()->ID() <<"   "<< m_colliders[i]->GetGameObject()->ID() << std::endl;
				//std::cout << "Objects are colliding: " << targetCollider->IsColliding(m_colliders[i]) << std::endl;

				if (targetCollider->GetGameObject()->ID() != m_colliders[colliderIndex]->GetGameObject()->ID() &&
					targetCollider->IsColliding(m_colliders[colliderIndex]))
				{
					
					return true;
				}
			}
			
		}

	}
	return false;
}
