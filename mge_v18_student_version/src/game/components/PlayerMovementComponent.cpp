#include "PlayerMovementComponent.h"
#include "mge/core/GameObject.hpp"
#include "game/components/PlayerDataComponent.h"
#include "game/MainWorld.h"
#include "game/components/GridComponent.h"
#include "mge/components/CircleCollider.h"
void PlayerMovementComponent::Awake()
{
	m_rigidbody = m_gameObject->GetComponent<RigidBody>();
	m_playerData = m_gameObject->GetComponent<PlayerDataComponent>();
	m_grid = dynamic_cast<MainWorld*>(m_gameObject->GetWorld())->GetGrid();
}

void PlayerMovementComponent::Start()
{
	m_initSpeed = m_rigidbody->GetMaxSpeed();
	//m_gameObject->GetComponent<CircleCollider>()->SetTrigger(true);
}

void PlayerMovementComponent::Update(float timeStep)
{
	//std::cout << "DIRECTION: " << currentDirection << std::endl;

	if (glm::length(m_rigidbody->velocity) > 0)
	{
		TileComponent* tile = m_grid->GetTileOnPos(m_gameObject->transform->LocalPosition());
		if (tile != nullptr)
		{
			if (tile->GetTileType() == TileType::DEFAULT)
			{
				m_rigidbody->SetMaxSpeed(m_initSpeed);

			}
			else if (tile->GetTileType() == m_playerData->MatType())
			{
				m_rigidbody->SetMaxSpeed(m_initSpeed + m_speedUpAmount);
			}
			else
			{
				m_rigidbody->SetMaxSpeed(m_initSpeed - m_slowDownAmount);
			}
		}
	}
	ApplyDirection();
	ApplyMovement();
}

void PlayerMovementComponent::ApplyDirection()
{
	bool keyPressed = false;
	Direction priorityDirection=NONE;
	//Direction newDirection=NONE;
	if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::D : sf::Keyboard::Right))
	{
		if (m_oldFirection == LEFT || m_oldFirection == RIGHT)
		{
			priorityDirection = RIGHT;
		}
		m_currentDirection = RIGHT;
		keyPressed = true;
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::A : sf::Keyboard::Left))
	{
		if (m_oldFirection == LEFT || m_oldFirection == RIGHT)
		{
			priorityDirection = LEFT;
		}
		m_currentDirection = LEFT;
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::S : sf::Keyboard::Down))
	{
		if (m_oldFirection == FORWARD || m_oldFirection == BACKWARD)
		{
			priorityDirection = BACKWARD;
		}
		m_currentDirection = BACKWARD;
		keyPressed = true;
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::W : sf::Keyboard::Up))
	{
		if (m_oldFirection == FORWARD || m_oldFirection == BACKWARD)
		{
			priorityDirection = FORWARD;
		}
		m_currentDirection = FORWARD;
		keyPressed = true;
	}

	if (priorityDirection != NONE)
	{
		m_currentDirection = priorityDirection;
	}

	if(!keyPressed)
	{
		m_currentDirection = NONE;
	}
	m_oldFirection = m_currentDirection;
}

void PlayerMovementComponent::ApplyMovement()
{

	if (m_currentDirection == RIGHT)
	{
		m_rigidbody->SetAcceleration(glm::vec2(-m_speed, 0));
		SetRotation(glm::vec3(1, 0, 0), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (m_currentDirection == LEFT)
	{
		m_rigidbody->SetAcceleration(glm::vec2(m_speed, 0));
		SetRotation(glm::vec3(-1, 0, 0), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (m_currentDirection == BACKWARD)
	{
		m_rigidbody->SetAcceleration(glm::vec2(0, -m_speed));
		SetRotation(glm::vec3(0, 0, 1), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (m_currentDirection == FORWARD)
	{
		m_rigidbody->SetAcceleration(glm::vec2(0, m_speed));

		SetRotation(glm::vec3(0, 0, -1), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (m_currentDirection == NONE)
	{
		m_rigidbody->SetAcceleration(glm::vec2(0, 0));
		m_rigidbody->velocity = glm::vec2(0, 0);
	}

}

void PlayerMovementComponent::SetPlayerNumber(int playerNumber)
{
	m_playerNumber = playerNumber;
}

void PlayerMovementComponent::SetArenaData(glm::vec2 pos, glm::vec2 size)
{
	m_arenaPosition = pos;
	m_arenaSize = size;
}

void PlayerMovementComponent::SetSpeed(float speed)
{
	m_speed = speed;
}

PlayerMovementComponent::Direction PlayerMovementComponent::GetCurrentDirection()
{
	return m_currentDirection;
}

PlayerMovementComponent::PlayerMovementComponent()
{
}


PlayerMovementComponent::~PlayerMovementComponent()
{
}


void PlayerMovementComponent::SetRotation(glm::vec3 worldDirection, glm::vec3 localDirection)
{
	//COMPARE LEFT TO LEFT
	//RIGHT TO RIGHT
	//UP TO UP

	float currentAngle = glm::degrees(glm::acos(glm::dot(worldDirection, glm::normalize(localDirection))));
	//std::cout << "ANGLE: " << currentAngle << std::endl;
	m_gameObject->transform->Rotate(glm::radians(-currentAngle), glm::vec3(0, 1, 0));

}

void PlayerMovementComponent::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "speed")
		{
			m_speed = strtof(a->value(), 0);
		}
		else if(attributeName == "slowDownAmount")
		{
			m_slowDownAmount = strtof(a->value(), 0);
		}
		else if (attributeName == "speedUpAmount")
		{
			m_speedUpAmount = strtof(a->value(), 0);
		}

	}
}
