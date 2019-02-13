#include "CollisionManager.h"
#include "CollisionInfo.h"
#include "GameObject.hpp"

int CollisionManager::AddCollider(ColliderComponent * newCollider)
{
	std::cout << "Add collider" << std::endl;
	m_colliders.push_back(newCollider);
	return m_colliders.size();
}

bool CollisionManager::CheckCollisionInWorld(ColliderComponent * targetCollider)
{
	for (int i = m_colliders.size() - 1; i >= 0; --i)
	{
		//if its not me and I am colliding with other object
		if (targetCollider->id != m_colliders[i]->id  &&  targetCollider->IsColliding(m_colliders[i]))
		{
			CollisionInfo newCollisionInfo;
			newCollisionInfo.collider = m_colliders[i]->GetGameObject();
			targetCollider->GetGameObject()->OnTriggerStay(&newCollisionInfo);

			return true;
		}
	}
	return false;
}
