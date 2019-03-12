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
	
	if (m_isDead)
	{
		m_position_tween->onStep([this](float x, float y, float z) {tweenedVector.x = x; tweenedVector.y = y; tweenedVector.z = z; return false; });
		m_scale_tween->onStep([this](float x, float y, float z) {tweenedScale.x = x; tweenedScale.y = y; tweenedScale.z = z; return false; });

		//std::cout << "POSITION Progress " << m_position_tween->progress() << std::endl;
		//::cout << "SCALE    Progress " << m_scale_tween->progress() << std::endl;
		//When animation is finsihed
		if (m_position_tween->progress() >= 1&&m_scale_tween->progress()>=1)
		{
			//Remove player from the board
			std::cout << "TP OUT TP OUT TP OUT TP OUT TP OUT TP OUT" << std::endl;
			//m_gameObject->transform->SetLocalPosition(glm::vec3(999, 0, 999));
			
		}
		else
		{

			m_gameObject->transform->SetScale(tweenedScale);
			std::cout << "SCALE" << tweenedScale << std::endl;
			m_gameObject->transform->SetLocalPosition(tweenedVector);
		}
		//::cout << "VECTOR " << tweenedVector << std::endl;
		
	}
	if (m_isDead && m_respawnClock.getElapsedTime().asSeconds()>=(m_respawnTime +m_penaltyTime ))
	{
		Tweener::DeleteTween<float>(m_position_tween);
		Tweener::DeleteTween<float>(m_scale_tween);
		Respawn();
	}
}

void PlayerDataComponent::OnCollision(CollisionInfo * collisionInfo)
{
	return; //LEGACY CODE
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

	//UNPARRENT

	StartDeathAnimation();
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

void PlayerDataComponent::StartDeathAnimation()
{
	glm::vec3 currentPos = m_gameObject->transform->LocalPosition();
	float position_duration = .50f;
	float scale_duration = 1.0f;

	 m_position_tween= Tweener::GenerateTween<float>(
		 currentPos.x, currentPos.x, //X
		 currentPos.y, 0, //Y
		 currentPos.z, currentPos.z, //Z
		 position_duration*1000, position_duration * 1000, position_duration * 1000);

	 m_scale_tween = Tweener::GenerateTween<float>(
		 2, 3.5f, //X
		 2, 0.5f, //Y
		 2, 3.5f, //Z
		 scale_duration * 1000, scale_duration * 1000, scale_duration * 1000);
	 tweenedScale = glm::vec3(2, 2, 2);
}
