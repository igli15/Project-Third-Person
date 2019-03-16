#include "RotatingComponent.h"
#include "mge/core/GameObject.hpp"
#include "SFML/Window.hpp"
#include "mge/core/ResourceManager.h"
#include "mge/core/AbstractGame.hpp"

RotatingComponent::RotatingComponent()
{
}


RotatingComponent::~RotatingComponent()
{
}

void RotatingComponent::Update(float timeStep)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_gameObject->transform->Rotate(timeStep * glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	}

	//NOTE: uncomment this if you wanna check th difference between with and without normal mapping
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("containerMat"));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_gameObject->setMaterial(AbstractGame::Instance()->GetResourceManager()->GetMaterial("wallNON"));
	}
	*/
}
