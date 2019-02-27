#include "ShootingComponent.h"

#include "game/components/PlayerMovementComponent.h"
#include "game/components/GridComponent.h"
#include "mge/core/GameObject.hpp"
#include "game/components/TileComponent.h"

#include "game/MainWorld.h"

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
	
}

void ShootingComponent::Update(float timeStep)
{
	XMLComponent::Update(timeStep);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		ShootInk(4);
	}
}

void ShootingComponent::Parse(rapidxml::xml_node<>* compNode)
{
}

void ShootingComponent::ShootInk(float tileAmount)
{
	bool horizontalShooting = false;
	bool verticallShooting = false;
	switch (m_playerMovementComponent->GetCurrentDirection())
	{
	case PlayerMovementComponent::FORWARD:
		verticallShooting = true;
		break;
	case PlayerMovementComponent::BACKWARD:
		verticallShooting = true;
		tileAmount *= -1;
		break;
	case PlayerMovementComponent::LEFT:
		horizontalShooting = true;
		tileAmount *= -1;
		break;
	case PlayerMovementComponent::RIGHT:
		horizontalShooting = true;
		break;
	default:
		break;
	}
	auto tiles = m_gridComponent->GetNeighbourTiles(m_gameObject->transform->WorldPosition(), tileAmount, horizontalShooting, verticallShooting);
	
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i]->GetGameObject()->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("brickMat"));
	}

}

void ShootingComponent::SetGrid(GridComponent * grid)
{
	m_gridComponent = grid;
}
