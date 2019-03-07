#include "RefillStationComponent.h"
#include "mge/core/CollisionInfo.h"
#include "game/components/ShootingComponent.h"
#include "mge/components/ColliderComponent.hpp"

void RefillStationComponent::Start()
{
	std::cout << "			REFILL STATION" << std::endl;
	m_gameObject->GetComponent<ColliderComponent>()->SetTrigger(true);
}

void RefillStationComponent::Update()
{
}

void RefillStationComponent::OnTrigger(CollisionInfo * collisionInfo)
{
	std::cout << "Refilling" << std::endl;
	collisionInfo->collider->GetComponent<ShootingComponent>()->AddInk(m_inkGainRate);
}

RefillStationComponent::RefillStationComponent()
{
}


RefillStationComponent::~RefillStationComponent()
{
}

void RefillStationComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "inkGainRate")
		{
			m_inkGainRate = strtof(a->value(), 0);
		}

	}
}
