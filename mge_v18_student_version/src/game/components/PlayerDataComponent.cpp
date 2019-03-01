#include "PlayerDataComponent.h"
#include "HUDComponent.h"
#include "PlayerMovementComponent.h"
#include "ShootingComponent.h"
#include "../HUD.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"

PlayerDataComponent::PlayerDataComponent()
{
}


PlayerDataComponent::~PlayerDataComponent()
{
}

void PlayerDataComponent::Start()
{
	m_spawnPosition = m_gameObject->transform->LocalPosition();
	m_playerMovement = m_gameObject->GetComponent<PlayerMovementComponent>();
	m_playerMovement->SetPlayerNumber(m_playerNumber);

	m_shootingComponent = m_gameObject->GetComponent<ShootingComponent>();
	m_shootingComponent->SetPlayerNumber(m_playerNumber);

}

void PlayerDataComponent::Update(float timeStep)
{
}

void PlayerDataComponent::OnCollision(CollisionInfo * collisionInfo)
{
	//Only objects with rigidBody are players
	if (collisionInfo->collider->getName() == "player")
	{
		collisionInfo->collider->GetComponent<PlayerDataComponent>()->RespawnPlayer();
		RespawnPlayer();
	}
}

void PlayerDataComponent::SetPlayerNumber(int playerNumber)
{
	m_playerNumber = playerNumber;

	if (playerNumber == 1)
	{
		m_material = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaMat"));
		m_tileMaterial = TileType::LAVA;
	}
	else if (playerNumber == 2)
	{
		m_material = dynamic_cast<TextureMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("iceMat"));
		m_tileMaterial = TileType::ICE;
	}
}

int PlayerDataComponent::GetPlayerNumber()
{
	return m_playerNumber;
}

void PlayerDataComponent::RespawnPlayer()
{
	std::cout << "Respawning player to " << m_spawnPosition << std::endl;
	m_shootingComponent->ResetInkLevel();
	
	m_gameObject->transform->SetLocalPosition(m_spawnPosition);
}

void PlayerDataComponent::SetSpawnPosition(glm::vec3 newSpawnPosition)
{
	m_spawnPosition = newSpawnPosition;
}

void PlayerDataComponent::SetCurrentPositionAsSpawnPosisition()
{
	SetSpawnPosition(m_gameObject->transform->LocalPosition());
}

void PlayerDataComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "playerNumber")
		{
			SetPlayerNumber((int)strtof(a->value(), 0));

		}

	}
}

TileType PlayerDataComponent::MatType()
{
	return m_tileMaterial;
}
