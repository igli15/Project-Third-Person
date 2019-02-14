#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	//Adding default layer "all", inlcuding all colliders
	AddLayer("all");
}

void CollisionManager::AddLayer(std::string layerName)
{
	//Craeting new layer with empty vector of Colliders
	m_collisionLayers[layerName] = new std::vector<ColliderComponent*>();
}

int CollisionManager::AddCollider(ColliderComponent * newCollider, std::string layerName)
{
	//Checking if layerName exists in m_collisionLayers
	if (m_collisionLayers.count(layerName) > 0)
	{
		m_collisionLayers[layerName]->push_back(newCollider);
		std::cout << "Collider added to collision layer: "<<layerName << std::endl;
	}
	else
	{
		std::cout << "There is no collision layer with name " << layerName << std::endl;
		throw;
	}
	m_colliders.push_back(newCollider);
	return 0;
}

bool CollisionManager::CheckCollisionInWorld(ColliderComponent * targetCollider)
{
	for (int i = m_colliders.size() - 1; i >= 0; --i)
	{
		//if its not me and I am colliding with other object
		if (targetCollider->GetGameObject()->ID() != m_colliders[i]->GetGameObject()->ID() &&  targetCollider->IsColliding(m_colliders[i]))
		{
			return true;
		}
	}
	return false;
	std::map<std::string, std::vector<ColliderComponent*>*>::iterator layerIterator;

	for (layerIterator = m_collisionLayers.begin(); layerIterator != m_collisionLayers.end(); layerIterator++)
	{
		std::cout << layerIterator->first  // string (key)
			<< ':'
			<< layerIterator->second   // string's value 
			<< std::endl;
	}

}
