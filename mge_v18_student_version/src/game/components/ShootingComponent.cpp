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
#include <iostream>
#include "mge/core/Tweener.h"

ShootingComponent::ShootingComponent()
{
}


ShootingComponent::~ShootingComponent()
{
	Tweener::DeleteTween<float>(testTween);
}

void ShootingComponent::Start()
{
	XMLComponent::Start();
	m_playerMovementComponent = m_gameObject->GetComponent<PlayerMovementComponent>();

	HUD::GetHudComponent()->SetMaxInk(m_inkMaxLevel);
	
	//testTween = Tweener::GenerateTween<float>(m_inkMaxLevel,0,10000); 
	//*testTween = (*testTween).via(tweeny::easing::bounceOut);
}

void ShootingComponent::Update(float timeStep)
{
	XMLComponent::Update(timeStep);

	//testTween->onStep([this](float x) {m_inkLevel = x;  return false; });

	HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);

	OnKeyPressed(sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? (sf::Keyboard::F) : (sf::Keyboard::BackSpace)));
	if (m_isChraging)
	{
		//Update HUD info
		HUD::GetHudComponent()->UpdateInkStatus(m_inkLevel, m_playerNumber);

		//increase ammo untill it riches maxRange
		if (m_currentAmmo >= m_maxRange) return;
		m_currentAmmo+= m_rateOfGainInk;
		m_inkLevel-= m_rateOfGainInk;
	}
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
		}
		else if (attributeName == "rateOfInkGain")
		{
			m_rateOfGainInk = strtof(a->value(), 0);
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

	auto tiles = m_gridComponent->GetNeighbourTiles(m_gameObject->transform->WorldPosition(), otherPlayerPos, tileAmount, horizontalShooting, negtiveDirection, [enemy]() {enemy->GetComponent<PlayerDataComponent>()->RespawnPlayer(); });
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (GetGameObject()->GetComponent<PlayerDataComponent>()->MatType() == TileType::LAVA)
		{
			tiles[i]->PaintTile(TileType::LAVA);
		}
		else
		{
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
	//std::cout << "OnKeyEnter" << std::endl;

	//Start charging
	if (!m_isChraging)
	{
		//Dont charge if player doesnt have enough ink
		if (m_inkLevel - m_minRange < 0) return;
		//std::cout << "	Start Charging" << std::endl;
		m_currentAmmo = m_minRange- m_rateOfGainInk;
		m_inkLevel -= m_minRange- m_rateOfGainInk;

		m_isChraging = true;
	}
	if (m_isChraging && m_currentAmmo >= m_minRange)
	{
		//Shoot ink on range of m_currentAmmo
		//stop charging
		//std::cout << "	Shoot" << std::endl;
		//std::cout << "	Stop Charging" << std::endl;
		ShootInk((int)m_currentAmmo);
		m_currentAmmo = 0;
		m_isChraging = false;
	}
	


}

void ShootingComponent::OnKeyStay()
{
	//std::cout << "OnKeyStay" << std::endl;
}

void ShootingComponent::OnKeyExit()
{
	//std::cout << "OnKeyExit" << std::endl;
}
