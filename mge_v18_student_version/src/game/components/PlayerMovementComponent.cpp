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

PlayerMovementComponent::PlayerMovementComponent()
{
}


PlayerMovementComponent::~PlayerMovementComponent()
{
}
