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
	OnKeyPressed(sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? (sf::Keyboard::F) : (sf::Keyboard::BackSpace)));
	if (m_isChraging)
	{
		HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);
		if (m_currentAmmo >= m_maxRange) return;
		m_currentAmmo+=0.1f;
		m_inkLevel-=0.1f;
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
		tiles[i]->GetGameObject()->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("lavaMat"));
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

void ShootingComponent::OnKeyPressed(bool isKeyPressedThisFrame)
{
	if (!m_isKeyPresedLastFrame&&isKeyPressedThisFrame)
	{
		//OnKeyEnter
		OnKeyEnter();
	}
	if(m_isKeyPresedLastFrame&&isKeyPressedThisFrame)
	{
		//OnKeyStay
		OnKeyStay();
	}
	if (m_isKeyPresedLastFrame && !isKeyPressedThisFrame)
	{
		//OnKeyExit
		OnKeyExit();
	}
	m_isKeyPresedLastFrame = isKeyPressedThisFrame;
}

void ShootingComponent::OnKeyEnter()
{
	std::cout << "OnKeyEnter" << std::endl;

	//Start charging
	if (!m_isChraging)
	{
		//Dont charge if player doesnt have enough ink
		if (m_inkLevel - m_minRange < 0) return;
		std::cout << "	Start Charging" << std::endl;
		m_currentAmmo = m_minRange-0.1f;
		m_inkLevel -= m_minRange-0.1f;

		m_isChraging = true;
	}
	if (m_isChraging && m_currentAmmo >= m_minRange)
	{
		//Shoot ink on range of m_currentAmmo
		//stop charging
		std::cout << "	Shoot" << std::endl;
		std::cout << "	Stop Charging" << std::endl;
		ShootInk((int)m_currentAmmo);
		m_currentAmmo = 0;
		m_isChraging = false;
	}
	


}

void ShootingComponent::OnKeyStay()
{
	std::cout << "OnKeyStay" << std::endl;
}

void ShootingComponent::OnKeyExit()
{
	std::cout << "OnKeyExit" << std::endl;
}
