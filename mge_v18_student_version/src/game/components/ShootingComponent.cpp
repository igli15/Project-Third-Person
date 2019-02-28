#include "ShootingComponent.h"

#include "game/components/PlayerMovementComponent.h"
#include "game/components/GridComponent.h"
#include "mge/core/GameObject.hpp"
#include "game/components/TileComponent.h"
#include "game/components/ShootingComponent.h"
#include "game/HUD.h"
#include "game/MainWorld.h"
#include "game/components/HUDComponent.h"
#include "SFML/Window.hpp"
#include "mge/core/ResourceManager.h"

ShootingComponent::ShootingComponent()
{
}


ShootingComponent::~ShootingComponent()
{

}

void ShootingComponent::Start()
{
	XMLComponent::Start();
	m_playerMovementComponent = m_gameObject->GetComponent<PlayerMovementComponent>();
	//asdasd
}

void ShootingComponent::Update(float timeStep)
{
	XMLComponent::Update(timeStep);
	if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? (sf::Keyboard::F) : (sf::Keyboard::BackSpace)))
	{
		if (m_inkLevel <= 0)
		{
			m_inkLevel = 0;
			return;
		}
		ShootInk(m_shootingRange);
		m_inkLevel -= m_shootingRange;
		HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);
		/*
		std::cout << "PlayerPos: " << GetGameObject()->transform->LocalPosition() << std::endl;

		std::cout << "TileIndex: " << m_gridComponent->GetTilePlayerIsOn(GetGameObject()->transform->LocalPosition())->GridPos() << std::endl;

		std::cout << "TilePosition: " << m_gridComponent->GetTilePlayerIsOn(GetGameObject()->transform->LocalPosition())->GetGameObject()->transform->WorldPosition()<<std::endl;
		*/
	}


}

void ShootingComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "shootingRange")
		{
			m_shootingRange = (int)strtof(a->value(), 0);
		}

	}
}

void ShootingComponent::ShootInk(float tileAmount)
{
	bool horizontalShooting = false;
	bool negtiveDirection = false;
	switch (m_playerMovementComponent->GetCurrentDirection())
	{
	case PlayerMovementComponent::BACKWARD:

		break;
	case PlayerMovementComponent::FORWARD:
		negtiveDirection = true;
		break;
	case PlayerMovementComponent::LEFT:
		horizontalShooting = true;
		negtiveDirection = true;
		break;
	case PlayerMovementComponent::RIGHT:
		horizontalShooting = true;
		break;
	default:
		break;
	}
	auto tiles = m_gridComponent->GetNeighbourTiles(m_gameObject->transform->WorldPosition(), tileAmount, horizontalShooting, negtiveDirection);
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i]->GetGameObject()->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("brickMat"));
	}

	tiles.clear();

}

void ShootingComponent::SetPlayerNumber(int playerNumber)
{
	m_playerNumber = playerNumber;
}

void ShootingComponent::SetGrid(GridComponent * grid)
{
	m_gridComponent = grid;
}
