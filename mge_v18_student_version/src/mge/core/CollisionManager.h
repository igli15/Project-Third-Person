#pragma once
#include <vector>
#include "../components/ColliderComponent.hpp"

class ColliderComponent;

class CollisionManager 
{
public:
	void AddCollider(ColliderComponent* newCollider);
	bool CheckCollisionInWorld(ColliderComponent* targetCollider);
private:
	std::vector<ColliderComponent*> m_colliders;
};