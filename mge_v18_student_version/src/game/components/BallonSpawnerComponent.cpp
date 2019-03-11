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

void BallonSpawnerComponent::Start()
{
	XMLComponent::Start();

	m_parentTile = m_gameObject->GetComponent<TileComponent>();

	if (m_spawnOnStart)
	{
		SpawnBalloon();
	}

}

void BallonSpawnerComponent::Update(float timeStep)
{
	XMLComponent::Update(timeStep);

	if (m_balloonSpawnClock.getElapsedTime().asSeconds() >= m_balloonSpawnTime)
	{
		SpawnBalloon();
		m_balloonSpawnClock.restart();
	}

}

void BallonSpawnerComponent::OnDestroy()
{
	XMLComponent::OnDestroy();
	m_parentTile->SetGridElement(nullptr);
}

void BallonSpawnerComponent::SpawnBalloon()
{
	Balloon* balloon = m_gameObject->GetWorld()->Instantiate<Balloon>();

	balloon->transform->SetLocalPosition(m_parentTile->GetGameObject()->transform->WorldPosition() + glm::vec3(0, 1, 0));

	m_parentTile->SetGridElement(balloon->GetBalloonComponent());
}

void BallonSpawnerComponent::Parse(rapidxml::xml_node<>* compNode)
{

}
