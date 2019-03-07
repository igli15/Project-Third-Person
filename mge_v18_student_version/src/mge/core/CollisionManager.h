#pragma once
#include <vector>
#include "../components/ColliderComponent.hpp"

class ColliderComponent;

class CollisionManager 
{
public:
	int AddCollider(ColliderComponent* newCollider);
	void RemoveCollider(ColliderComponent* colliderToRemove);
	bool CheckCollisionInWorld(ColliderComponent* targetCollider);
private:
	std::vector<ColliderComponent*> m_colliders;
};