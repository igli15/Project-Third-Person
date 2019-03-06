#include "CollisionManager.h"
#include "../components//RigidBody.h"

int CollisionManager::AddCollider(ColliderComponent * newCollider)
{
	std::cout << "Add collider" << std::endl;
	m_colliders.push_back(newCollider);
	return m_colliders.size();
}

void CollisionManager::RemoveCollider(ColliderComponent * colliderToRemove)
{
	bool destroyed = false;
	for (int i = m_colliders.size()-1; i >=0; i--)
	{
		if (colliderToRemove->GetGameObject()->ID() == m_colliders[i]->GetGameObject()->ID())
		{
			m_colliders.erase(std::find(m_colliders.begin(), m_colliders.end(), m_colliders[i]));
			destroyed = true;
		}
	}
	std::cout << "			collider is destroyed: " << destroyed << std::endl;
}

bool CollisionManager::CheckCollisionInWorld(ColliderComponent * targetCollider)
{
	std::vector<std::string> filters = targetCollider->GetCollisionFilterTags();

	if (filters.size() == 0) return false;
	bool output = false;
	for (int colliderIndex = m_colliders.size() - 1; colliderIndex >= 0; --colliderIndex)
	{
		//std::cout << std::endl;
		for (int i = 0; i < filters.size(); i++)
		{
			//std::cout << "filter: " << filters[i] << ":"<< m_colliders[colliderIndex]->GetCollisionLayerTag() <<std::endl;
			if (//Comparing curretn filter with layer of object	
				m_colliders[colliderIndex]->GetCollisionLayerTag() == filters[i]  && 
				//Check if object isnt checking itself
				targetCollider->GetGameObject()->ID() != m_colliders[colliderIndex]->GetGameObject()->ID()
				)
			{
				//std::cout << "COLLIDER" << m_colliders[colliderIndex]->GetGameObject()->transform->LocalPosition() << std::endl;
				CollisionInfo* collisionInfo = targetCollider->IsColliding(m_colliders[colliderIndex]);
				if (collisionInfo!=nullptr)
				{
					//Calling RigidBody to resolve collision
					collisionInfo->collider = m_colliders[colliderIndex]->GetGameObject();

					//If collider is trigger, call onTrigger
					if (m_colliders[colliderIndex]->IsTrigger()) targetCollider->GetGameObject()->OnTrigger(collisionInfo);
					else targetCollider->GetGameObject()->GetRigidBody()->OnCollisionStay(collisionInfo);

					return true;
				}
				
			}
			
		}

	}
	return output;
}
