#include "RefillStationComponent.h"
#include "mge/core/CollisionInfo.h"
#include "game/components/ShootingComponent.h"

void RefillStationComponent::Start()
{
}

void RefillStationComponent::Update()
{
}

void RefillStationComponent::OnTrigger(CollisionInfo * collisionInfo)
{
	std::cout << "Refilling" << std::endl;
	collisionInfo->collider->GetComponent<ShootingComponent>()->ResetInkLevel();
}

RefillStationComponent::RefillStationComponent()
{
}


RefillStationComponent::~RefillStationComponent()
{
}
