#include "../components/KeyMoveComponent.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "game/MainGame.h"
#include "game/MainWorld.h"
#include "mge/core/WorldManager.h"

KeyMoveComponent::KeyMoveComponent() 
{
}

KeyMoveComponent::~KeyMoveComponent()
{
}

void KeyMoveComponent::Update(float timeStep)
{
	float moveSpeed = 0.0f; //default if no keys
	float turnSpeed = 0.0f;
	m_horizontalMoveSpeed = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
		moveSpeed = m_moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
		moveSpeed = -m_moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		turnSpeed = - m_turnSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		turnSpeed = +m_turnSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveSpeed = m_moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveSpeed = -m_moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_horizontalMoveSpeed = -m_moveSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_horizontalMoveSpeed = +m_moveSpeed;
	}
	//translate the object in its own local space
	m_gameObject->transform->Translate(glm::vec3(m_horizontalMoveSpeed*timeStep, 0.0f, moveSpeed * timeStep));


	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, then we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space
	m_gameObject->transform->Rotate(glm::radians(turnSpeed*timeStep), glm::vec3(0.0f, 1.0f, 0.0f));

	//NOTE:
	//The reason the above happens in the local space of the object and not in the world space
	//is that we use the _owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
	//The methods multiply the current transform with the translation/rotation matrix from left to right
	//meaning everything happens in local space.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		MainGame::Instance()->GetWorldManager()->CreateWorld<MainWorld>("Level1");
		//_owner->Destroy();
	}
}
