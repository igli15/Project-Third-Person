#include "CollisionManager.h"

void CollisionManager::AddCollider(ColliderComponent * newCollider)
{
	m_colliders.push_back(newCollider);
}

bool CollisionManager::CheckCollisionInWorld(ColliderComponent * targetCollider)
{
	for (int i = m_colliders.size() - 1; i >= 0; --i)
	{
		if (targetCollider == m_colliders[i])
		{
			//Dont check collision with itself
		}
		if (targetCollider->IsColliding(m_colliders[i]))
		{
			std::cout << "CollisionManager => Collision detected ";
			return true;
		}
	}
	return false;
}
