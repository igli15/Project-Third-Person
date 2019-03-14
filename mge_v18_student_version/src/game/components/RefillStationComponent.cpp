#include "RefillStationComponent.h"
#include "mge/core/CollisionInfo.h"
#include "game/components/ShootingComponent.h"
#include "mge/components/ColliderComponent.hpp"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/GameObject.hpp"
#include "mge/materials/TextureMaterial.hpp"

void RefillStationComponent::Start()
{
	std::cout << "			REFILL STATION" << std::endl;
	m_gameObject->GetComponent<ColliderComponent>()->SetTrigger(true);
	m_initMusic = AbstractGame::Instance()->GetResourceManager()->GetMusic("");
	m_audioSource = m_gameObject->AddComponent<AudioSource>();
	m_audioSource->SetMusic(m_initMusic);
}

void RefillStationComponent::Update(float timeStep)
{
	Component::Update(timeStep);

	
	if (!isBlinking) return;
	std::cout << "BLINK   " << isBlinking << std::endl;
	

	if (m_animationClock.getElapsedTime().asSeconds() < 0.5f)
	{
		//dynamic_cast<TextureMaterial*> (m_gameObject->getMaterial())->SetEmissionScale(0); //NOT BLINK
		m_gameObject->transform->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
	}
	if (m_animationClock.getElapsedTime().asSeconds() >= 0.5f&&m_animationClock.getElapsedTime().asSeconds() < 1)
	{
		//dynamic_cast<TextureMaterial*> (m_gameObject->getMaterial())->SetEmissionScale(1); //BLINK
		m_gameObject->transform->SetScale(glm::vec3(1, 1, 1));
	}
	if (m_animationClock.getElapsedTime().asSeconds() > 1)
	{
		m_animationClock.restart();
	}
}

void RefillStationComponent::OnTrigger(CollisionInfo * collisionInfo)
{
	std::cout << "Refilling" << std::endl;
	
	m_timeTillPlay -= 0.05f;
	if (m_timeTillPlay < 0)
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

void RefillStationComponent::Blink(bool blink)
{
	isBlinking = blink;
	if (!blink)
	{
		m_gameObject->transform->SetScale(glm::vec3(1, 1, 1));
	}
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
