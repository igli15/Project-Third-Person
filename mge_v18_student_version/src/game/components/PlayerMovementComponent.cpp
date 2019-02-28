#include "PlayerMovementComponent.h"
#include "mge/core/GameObject.hpp"

void PlayerMovementComponent::Awake()
{
	m_rigidbody = m_gameObject->GetComponent<RigidBody>();
}

void PlayerMovementComponent::Start()
{
}

void PlayerMovementComponent::Update(float timeStep)
{
	//std::cout << "DIRECTION: " << currentDirection << std::endl;

	//Prevent player moving out of arena boundaries
	if (IsOutOfBorder())
	{
		m_rigidbody->SetAcceleration(glm::vec2(0, 0));
		m_gameObject->transform->Translate(-glm::vec3(m_rigidbody->velocity.x, 0, m_rigidbody->velocity.y));
		m_rigidbody->velocity = glm::vec2(0, 0);
		return;
	}
	if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::D : sf::Keyboard::Right))
	{
		m_currentDirection = RIGHT;
		m_rigidbody->SetAcceleration(glm::vec2(-m_speed, 0));
		SetRotation(glm::vec3(-1, 0, 0), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::A : sf::Keyboard::Left))
	{
		m_currentDirection = LEFT;
		m_rigidbody->SetAcceleration(glm::vec2(m_speed, 0));
		SetRotation(glm::vec3(1, 0, 0), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::S : sf::Keyboard::Down))
	{
		m_currentDirection = BACKWARD;
		m_rigidbody->SetAcceleration(glm::vec2(0, -m_speed));
		SetRotation(glm::vec3(0, 0, -1), m_gameObject->transform->LocalTransform()[2]);
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::W : sf::Keyboard::Up))
	{
		m_currentDirection = FORWARD;
		m_rigidbody->SetAcceleration(glm::vec2(0, m_speed));

		SetRotation(glm::vec3(0,0,1),m_gameObject->transform->LocalTransform()[2]);
	}
	else
	{
		m_rigidbody->SetAcceleration(glm::vec2(0, 0));
		m_rigidbody->velocity = glm::vec2(0, 0);
	}
}

void PlayerMovementComponent::OnCollision(CollisionInfo * collisionInfo)
{
	//std::cout << "COLLISION IS CALLED IN COMPONENT" << std::endl;
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

bool PlayerMovementComponent::IsOutOfBorder()
{
	return false;

	glm::vec2 newPos = glm::vec2(m_gameObject->transform->LocalPosition().x, m_gameObject->transform->LocalPosition().z) + m_rigidbody->velocity;

	/*
	std::cout << std::endl<< "NewPosition" << newPos << std::endl;
	std::cout << "Arena Left: " << m_arenaPosition.x - m_arenaSize.x << std::endl;
	std::cout << "Arena Right: " << m_arenaPosition.x << std::endl;

	std::cout << "Arena Up: " << m_arenaPosition.y + m_arenaSize.y << std::endl;
	std::cout << "Arena Down: " << m_arenaPosition.y << std::endl;
	*/
	if (newPos.x<m_arenaPosition.x-m_arenaSize.x || newPos.x>m_arenaPosition.x) return true;
	if (newPos.y<m_arenaPosition.y|| newPos.y > m_arenaPosition.y+m_arenaSize.y) return true;

	return false;
}

void PlayerMovementComponent::SetRotation(glm::vec3 worldDirection, glm::vec3 localDirection)
{
	//COMPARE LEFT TO LEFT
	//RIGHT TO RIGHT
	//UP TO UP

	float currentAngle = glm::degrees( glm::acos(glm::dot(worldDirection, glm::normalize(localDirection))) );
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

	}
}
