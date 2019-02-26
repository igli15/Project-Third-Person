#include "PlayerMovementComponent.h"



void PlayerMovementComponent::Awake()
{
	m_rigidbody = m_gameObject->GetComponent<RigidBody>();
}

void PlayerMovementComponent::Start()
{
}

void PlayerMovementComponent::Update(float timeStep)
{

	float speed = 0.1f;
	if (IsOutOfBorder())
	{
		
		m_rigidbody->SetAcceleration(glm::vec2(0, 0));
		m_gameObject->transform->Translate(-glm::vec3(m_rigidbody->velocity.x, 0, m_rigidbody->velocity.y));
		m_rigidbody->velocity = glm::vec2(0, 0);
		return;
	}
	if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::D : sf::Keyboard::Right))
	{
		//rigidbody->velocity.x = speed;
		m_rigidbody->SetAcceleration(glm::vec2(speed, 0));
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::A : sf::Keyboard::Left))
	{
		//rigidbody->velocity.x = -speed;
		m_rigidbody->SetAcceleration(glm::vec2(-speed, 0));
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::S : sf::Keyboard::Down))
	{
		//rigidbody->velocity.y = speed;
		m_rigidbody->SetAcceleration(glm::vec2(0, speed));
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::W : sf::Keyboard::Up))
	{
		//rigidbody->velocity.y = -speed;
		m_rigidbody->SetAcceleration(glm::vec2(0, -speed));
	}
	else
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

PlayerMovementComponent::PlayerMovementComponent()
{
}


PlayerMovementComponent::~PlayerMovementComponent()
{
}

bool PlayerMovementComponent::IsOutOfBorder()
{
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
