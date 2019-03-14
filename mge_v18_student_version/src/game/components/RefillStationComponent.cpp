#include "RefillStationComponent.h"
#include "mge/core/CollisionInfo.h"
#include "game/components/ShootingComponent.h"
#include "mge/components/ColliderComponent.hpp"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/GameObject.hpp"


void RefillStationComponent::Start()
{
	std::cout << "			REFILL STATION" << std::endl;
	m_gameObject->GetComponent<ColliderComponent>()->SetTrigger(true);
	m_initMusic = AbstractGame::Instance()->GetResourceManager()->GetMusic("");
	m_audioSource = m_gameObject->AddComponent<AudioSource>();
	m_audioSource->SetMusic(m_initMusic);
}

void RefillStationComponent::Update()
{
}

void RefillStationComponent::OnTrigger(CollisionInfo * collisionInfo)
{
	std::cout << "Refilling" << std::endl;
	
	m_timeTillPlay -= 0.05f;
	if (m_timeTillPlay < -1)
	{
		m_audioSource->PlayOneShotSound("refillSound");
		m_timeTillPlay = 1.6f;
	}
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
