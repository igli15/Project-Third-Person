#include "CannonComponent.h"
#include "GridComponent.h"
#include "mge/core/GameObject.hpp"
#include "PlayerDataComponent.h"
#include "mge/components/AudioSource.h"
#include <SFML\Audio.hpp>
#include "mge/core/AbstractGame.hpp"
#include "mge/core/ResourceManager.h"

CannonComponent::CannonComponent()
{

}


CannonComponent::~CannonComponent()
{
}

void CannonComponent::OnPainted(PlayerDataComponent* playerData)
{
	ShootInFacingDir(playerData);

	m_gameObject->transform->Rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));

	switch (m_facingDir)
	{
	case Direction::UP:
		m_facingDir = Direction::RIGHT;
		break;
	case Direction::DOWN:
		m_facingDir = Direction::LEFT;
		break;
	case Direction::LEFT:
		m_facingDir = Direction::UP;
		break;
	case Direction::RIGHT:
		m_facingDir = Direction::DOWN;
		break;
	default:
		break;
	}

	ShootInFacingDir(playerData);

}

void CannonComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();
		if (attributeName == "FacingDir")
		{
			std::string value(a->value());
			if (value == "UP")
			{
				m_facingDir = Direction::UP;
			}
			else if (value == "DOWN")
			{
				m_facingDir = Direction::DOWN;
			}
			else if (value == "RIGHT")
			{
				m_facingDir = Direction::RIGHT;
			}
			else if (value == "LEFT")
			{
				m_facingDir = Direction::LEFT;
			}
		}
		else if (attributeName == "shootingRange")
		{
			m_shootingRange = (int)strtof(a->value(), 0);
		}
	}
}

void CannonComponent::Start()
{
	m_grid->GetTileOnPos(m_gameObject->transform->WorldPosition())->SetGridElement(this);
	m_initMusic = AbstractGame::Instance()->GetResourceManager()->GetMusic("");
	m_audioSource = m_gameObject->AddComponent<AudioSource>();
	m_audioSource->SetMusic(m_initMusic);
}

void CannonComponent::ShootInFacingDir(PlayerDataComponent* playerData)
{
	bool horizontal;
	bool positive;

	if (shot)return;
	
	m_audioSource->PlayOneShotSound("cannonShot");
	
	switch (m_facingDir)
	{
	case Direction::UP:
		horizontal = false;
		positive = true;
		break;
	case Direction::DOWN:
		horizontal = false;
		positive = false;
		break;
	case Direction::LEFT:
		horizontal = true;
		positive = true;
		break;
	case Direction::RIGHT:
		horizontal = true;
		positive = false;
		break;
	default:
		break;
	}
	auto tiles = m_grid->GetNeighbourTiles(m_gameObject->transform->LocalPosition(), playerData->GetEnemy()->transform->LocalPosition(),
		m_shootingRange, horizontal, positive, [playerData, this]() {shot = true;  playerData->GetEnemy()->GetComponent<PlayerDataComponent>()->OnDeath(); shot = false; });

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->GridPos() != m_tile->GridPos())
		{
			tiles[i]->ActivateGridElement(playerData);
		}
		tiles[i]->PaintTile(playerData->MatType());
	}
}
