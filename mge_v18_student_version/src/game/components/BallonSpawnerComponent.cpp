#include "BallonSpawnerComponent.h"
#include "mge/core/GameObject.hpp"
#include "game/components/TileComponent.h"
#include "mge/core/World.hpp"
#include "game/Balloon.h"
#include "game/components/BalloonComponent.h"

BallonSpawnerComponent::BallonSpawnerComponent()
{
}


BallonSpawnerComponent::~BallonSpawnerComponent()
{
}

void BallonSpawnerComponent::Awake()
{
	m_parentTile = m_gameObject->GetComponent<TileComponent>();
}

void BallonSpawnerComponent::Start()
{
	XMLComponent::Start();



}

void BallonSpawnerComponent::Update(float timeStep)
{
	XMLComponent::Update(timeStep);
	if (m_spawnOnStart)
	{
		SpawnBalloon();

		m_spawnOnStart = false;
	}

	if (m_balloonSpawnClock.getElapsedTime().asSeconds() > m_balloonSpawnTime)
	{
		Balloon* b = SpawnBalloon();
		if (b != nullptr)
		{
			b->ScaleUp();
		}
		m_balloonSpawnClock.restart();
	}

}

void BallonSpawnerComponent::OnDestroy()
{
	XMLComponent::OnDestroy();
	m_parentTile->SetGridElement(nullptr);
}

Balloon* BallonSpawnerComponent::SpawnBalloon()
{
	if (!m_parentTile->IsFree()) return nullptr;


	Balloon* balloon = m_gameObject->GetWorld()->Instantiate<Balloon>();

	balloon->transform->SetLocalPosition(m_parentTile->GetGameObject()->transform->WorldPosition() + glm::vec3(0, 1, 0));
	m_parentTile->SetGridElement(balloon->GetBalloonComponent());

	return balloon;
}

void BallonSpawnerComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "spawnTime")
		{
			m_balloonSpawnTime = strtof(a->value(), 0);
		}
		else if (attributeName == "spawnOnStart")
		{
			std::string value(a->value());
			m_spawnOnStart = (value == "True");
		}
	}
}
