#include "CollisionManager.h"

void CollisionManager::AddCollider(ColliderComponent * newCollider)
{
	m_colliders.push_back(newCollider);
}
