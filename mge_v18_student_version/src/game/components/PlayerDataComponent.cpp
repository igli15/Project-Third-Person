#include "PlayerDataComponent.h"
#include "HUDComponent.h"
#include "PlayerMovementComponent.h"
#include "ShootingComponent.h"
#include "../HUD.h"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"
#include "game/components/GridComponent.h"
#include "game/MainWorld.h"

PlayerDataComponent::PlayerDataComponent()
{
}


PlayerDataComponent::~PlayerDataComponent()
{
}

void PlayerDataComponent::Start()
{
	m_playerMovement = m_gameObject->GetComponent<PlayerMovementComponent>();
	m_playerMovement->SetPlayerNumber(m_playerNumber);

	m_shootingComponent = m_gameObject->GetComponent<ShootingComponent>();
	m_shootingComponent->SetPlayerNumber(m_playerNumber);

	m_levelGrid = dynamic_cast<MainWorld*>(GetGameObject()->GetWorld())->GetGrid();
}

void PlayerDataComponent::Update(float timeStep)
{
	if(m_isDead) std::cout << "time left: " << (m_respawnTime + m_penaltyTime) - m_respawnClock.getElapsedTime().asSeconds() << std::endl;
	if (m_isDead && m_respawnClock.getElapsedTime().asSeconds()>=(m_respawnTime +m_penaltyTime ))
	{
		Respawn();
	}
}

void PlayerDataComponent::OnCollision(CollisionInfo * collisionInfo)
{
	//Only objects with rigidBody are players
	if (collisionInfo->collider->getName() == "player")
	{
		collisionInfo->collider->GetComponent<PlayerDataComponent>()->OnDeath();
		OnDeath();
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

void PlayerDataComponent::OnDeath()
{
	//EXPLODE PLAYER in enemy color
	auto tiles = m_levelGrid->GetTilesInARange(GetGameObject()->transform->WorldPosition(),m_explosionWidth,m_explosionHeight);
	TileType enemyTileType;

	m_gameObject->transform->SetLocalPosition(glm::vec3(999, 0, 999));

	if (m_tileMaterial == TileType::ICE)
	{
		enemyTileType = TileType::LAVA;
	}
	else
	{
		enemyTileType = TileType::ICE;
	}

	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i]->ActivateGridElement(GetEnemy()->GetComponent<PlayerDataComponent>());
		tiles[i]->PaintTile(enemyTileType);
	}

	m_respawnClock.restart();
	m_isDead = true;
	m_penaltyTime = m_levelGrid->GetTileCount(m_playerNumber == 1 ? TileType::LAVA : TileType::ICE)*m_penaltyTimePerTile;
	
	HUD* hud = dynamic_cast<HUD*>(HUD::GetHudComponent()->GetGameObject());
	hud->SetRespawnTime(m_playerNumber, m_penaltyTime);
}

void PlayerDataComponent::Respawn()
{
	//Teleporting player back to spawn position
	std::cout << "Respawning player to " << m_spawnPosition << std::endl;
	m_shootingComponent->ResetInkLevel();
	m_gameObject->transform->SetLocalPosition(m_spawnPosition);
	m_isDead = false;
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
		else if (attributeName == "respawnPosition")
		{
			glm::vec3 pos;
			sscanf(a->value(), "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
			m_spawnPosition = pos;
		}
		else if (attributeName == "explosionWidth")
		{
			m_explosionWidth = (int)(strtof(a->value(), 0));
		}
		else if (attributeName == "explosionHeight")
		{
			m_explosionHeight = (int)(strtof(a->value(), 0));
		}

	}
}

TileType PlayerDataComponent::MatType()
{
	return m_tileMaterial;
}

bool PlayerDataComponent::IsDead()
{
	return m_isDead;
}

GameObject * PlayerDataComponent::GetEnemy()
{
	if (m_playerNumber == 1)
	{
		return dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(1);
	}
	else if (m_playerNumber == 2)
	{
		return dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(0);
	}
}
