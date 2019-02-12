#include "ColliderComponent.hpp"



void ColliderComponent::Awake()
{
	AbstractGame::Instance()->GetCollisionManager()->AddCollider(this);
}

void ColliderComponent::Update(float timeSteps)
{

	//Update
}
