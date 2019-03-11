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
#include "game/components/PlayerDataComponent.h"

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
	m_playerDataCompoent = m_gameObject->GetComponent<PlayerDataComponent>();

	HUD::GetHudComponent()->SetMaxInk(m_inkMaxLevel);

	//Registering input function to Key F
	//Primary shooting
	keyOne = new KeyObject((m_playerNumber == 1) ? (sf::Keyboard::F) : (sf::Keyboard::BackSpace));
	keyOne->onKeyEnter = ([this]() {OnKeyOneEnter(); });
	keyOne->onKeyStay = ([this]() {OnKeyOneStay(); });
	keyOne->onKeyExit = ([this]() {OnKeyOneExit(); });

	keyTwo = new KeyObject((m_playerNumber == 1) ? (sf::Keyboard::C) : (sf::Keyboard::Equal));
	keyTwo->onKeyEnter = ([this]() {OnKeyTwoEnter(); });
}

void ShootingComponent::Update(float timeStep)
{
	XMLComponent::Update(timeStep);
	keyOne->KeyPressed();
	keyTwo->KeyPressed();
	//OnKeyOnePressed(sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? (sf::Keyboard::F) : (sf::Keyboard::BackSpace)));
}

void ShootingComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "minRange")
		{
			m_minRange = (int)strtof(a->value(), 0);
		}
		else if (attributeName == "maxRange")
		{
			m_maxRange = (int)strtof(a->value(), 0);
		}
		else if (attributeName == "inkMaxLevel")
		{
			m_inkMaxLevel = (int)strtof(a->value(), 0);
			m_inkLevel = m_inkMaxLevel;
		}
		else if (attributeName == "rateOfInkGain")
		{
			m_rateOfGainInk = strtof(a->value(), 0);
		}

	}
}

void ShootingComponent::ShootInk(float tileAmount, bool isPrimaryShooting)
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

	glm::vec3 otherPlayerPos;
	GameObject* enemy;
	if (m_playerNumber == 1)
	{
		enemy = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(1);
		otherPlayerPos = enemy->transform->WorldPosition();
	}
	else
	{
		enemy = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetPlayer(0);
		otherPlayerPos = enemy->transform->WorldPosition();
	}


	//std::cout << m_gameObject->transform->WorldPosition() << " ==== " << otherPlayerPos << std::endl;

	std::vector<TileComponent*> tiles;

	if (isPrimaryShooting)
	{

		tiles = m_gridComponent->GetNeighbourTiles(m_gameObject->transform->WorldPosition(), otherPlayerPos, tileAmount, horizontalShooting, negtiveDirection, [enemy]() {enemy->GetComponent<PlayerDataComponent>()->OnDeath(); });
	}
	else 
	{
		tiles = m_gridComponent->GetTilesInTriangleRange(m_gameObject->transform->WorldPosition(), otherPlayerPos, tileAmount, horizontalShooting, negtiveDirection, [enemy]() {enemy->GetComponent<PlayerDataComponent>()->OnDeath(); });
	}
	for (int i = 0; i < tiles.size(); i++)
	{
		if (m_playerDataCompoent->MatType() == TileType::LAVA)
		{
			tiles[i]->ActivateGridElement(m_playerDataCompoent);
			tiles[i]->PaintTile(TileType::LAVA);
		}
		else
		{
			tiles[i]->ActivateGridElement(m_playerDataCompoent);
			tiles[i]->PaintTile(TileType::ICE);
		}
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

void ShootingComponent::SetInkLevel(float newInkLevel)
{
	m_inkLevel = newInkLevel;
	HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);
}

void ShootingComponent::ResetInkLevel()
{
	SetInkLevel(m_inkMaxLevel);
}

void ShootingComponent::AddInk(float inkLevel)
{
	//Incrasing Ink level
	m_inkLevel += inkLevel;
	if (m_inkLevel >= m_inkMaxLevel) m_inkLevel = m_inkMaxLevel;
	//Update HUD after changing Ink level
	HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);
}

void ShootingComponent::OnKeyOneEnter()
{
	
}

void ShootingComponent::OnKeyOneStay()
{
	//std::cout << "OnKeyStay" << std::endl;
	if (m_playerDataCompoent->IsDead()) return;
	//std::cout << "OnKeyEnter" << std::endl;

	//Start charging
	if (!m_isChraging && m_clock1.getElapsedTime().asSeconds() >= m_reloadTime1)
	{
		//std::cout << "TIME: " << m_clock1.getElapsedTime().asSeconds() <<"|"<< m_reloadTime1 << std::endl;
		//Dont charge if player doesnt have enough ink
		if (m_inkLevel - m_minRange < 0) return;
		//std::cout << "	Start Charging" << std::endl;
		m_currentAmmo = m_minRange - m_rateOfGainInk;
		m_inkLevel -= m_minRange - m_rateOfGainInk;

		m_isChraging = true;
	}
	if (m_isChraging)
	{
		//Update HUD info
		HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);

		//increase ammo untill it riches maxRange
		if (m_currentAmmo >= m_maxRange) return;
		m_currentAmmo += m_rateOfGainInk;
		m_inkLevel -= m_rateOfGainInk;
	}
}
void ShootingComponent::OnKeyOneExit()
{
	//std::cout << "OnKeyExit" << std::endl;
	if (m_isChraging && m_currentAmmo >= m_minRange)
	{
		//Shoot ink on range of m_currentAmmo
		//stop charging
		ShootInk((int)m_currentAmmo, true);
		m_currentAmmo = 0;
		m_isChraging = false;
		m_clock1.restart();
	}
}

void ShootingComponent::OnKeyTwoEnter()
{
	if (m_clock2.getElapsedTime().asSeconds() < m_relaodTime2) return;
	ShootInk(3, false);
	m_clock2.restart();
}

void ShootingComponent::OnKeyTwoStay()
{
}

void ShootingComponent::OnKeyTwoExit()
{
}


