#include "CollisionManager.h"
#include "../components//RigidBody.h"

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
				
			if (//Comparing curretn filter with layer of object	
				m_colliders[colliderIndex]->GetCollisionLayerTag() == filters[i]  && 
				//Check if object isnt checking itself
				targetCollider->GetGameObject()->ID() != m_colliders[colliderIndex]->GetGameObject()->ID()
				)
			{
				CollisionInfo* collisionInfo = targetCollider->IsColliding(m_colliders[colliderIndex]);
				if (collisionInfo!=nullptr)
				{
					std::cout << "COLLISION" << std::endl;
					//TODO: replace by add direct reference to rb in gameobject
					targetCollider->GetGameObject()->GetComponent<RigidBody>()->OnCollisionStay(collisionInfo);
					return true;
				}
				
			}
			
		}

	}
	return false;
}
