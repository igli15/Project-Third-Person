#pragma once
#include <vector>
#include "../components/ColliderComponent.hpp"

class CollisionManager 
{
public:
	void AddCollider(ColliderComponent* newCollider);
private:
	std::vector<ColliderComponent*> m_colliders;
};