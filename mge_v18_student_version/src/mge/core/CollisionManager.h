#pragma once
#include <vector>
#include <map>

#include "../components/ColliderComponent.hpp"

class ColliderComponent;

class CollisionManager 
{
public:
	CollisionManager();
	void AddLayer(std::string layerName);
	int AddCollider(ColliderComponent* newCollider, std::string layerName="all");
	bool CheckCollisionInWorld(ColliderComponent* targetCollider);


private:
	std::vector<ColliderComponent*> m_colliders;
	std::map<std::string, std::vector<ColliderComponent*>*> m_collisionLayers;
};