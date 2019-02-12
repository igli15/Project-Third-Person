#include "ColliderComponent.hpp"



void ColliderComponent::Awake()
{
	id=AbstractGame::Instance()->GetCollisionManager()->AddCollider(this);
}

void ColliderComponent::Update(float timeSteps)
{

	//Update
}
