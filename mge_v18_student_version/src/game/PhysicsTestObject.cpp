#include "PhysicsTestObject.h"

#include "mge/components/CircleCollider.h"
#include <SFML/Window/Keyboard.hpp>

PhysicsTestObject::PhysicsTestObject()
{
}


PhysicsTestObject::~PhysicsTestObject()
{
}

void PhysicsTestObject::Load()
{
	//AddComponets here
	circleCollider= AddComponent<CircleCollider>();
	
	rigidbody=AddComponent<RigidBody>();
	rigidbody->SetCollider(circleCollider);


}

void PhysicsTestObject::Start()
{
	GameObject::Start();
	
	circleCollider->SetCollisionLayerTag("players");
	circleCollider->AddCollisionFilterTag("players");

	transform->SetLocalPosition(glm::vec3(5, 0, 0));
	SetMeshRenderer(this->AddComponent<MeshRenderer>());
	//GetMeshRenderer()->SetMesh(cylinderMesh);
	//setMaterial(brickMat);
	transform->Scale(glm::vec3(1, 1, 1));
	rigidbody->SetMaxSpeed(0.5f);
}

void PhysicsTestObject::Update(float timeStep)
{
	GameObject::Update(timeStep);
	

	float speed = 0.1f;

	if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::D: sf::Keyboard::Right))
	{
		//rigidbody->velocity.x = speed;
		rigidbody->SetAcceleration(glm::vec2(speed,0));
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::A : sf::Keyboard::Left))
	{
		//rigidbody->velocity.x = -speed;
		rigidbody->SetAcceleration(glm::vec2(-speed, 0));
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::S : sf::Keyboard::Down))
	{
		//rigidbody->velocity.y = speed;
		rigidbody->SetAcceleration(glm::vec2(0, speed));
	}
	else if (sf::Keyboard::isKeyPressed((m_playerNumber == 1) ? sf::Keyboard::W : sf::Keyboard::Up))
	{
		 //rigidbody->velocity.y = -speed;
		rigidbody->SetAcceleration(glm::vec2(0, -speed));
	}
	else
	{
		rigidbody->SetAcceleration(glm::vec2(0, 0));
		rigidbody->velocity = glm::vec2(0, 0);
	}
	
}

void PhysicsTestObject::SetPlayer(float playerNumber)
{
	m_playerNumber = playerNumber;
}
