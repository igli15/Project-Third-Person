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
	ColliderComponent* collider= AddComponent<CircleCollider>();
	rigidbody=AddComponent<RigidBody>();
	rigidbody->SetCollider(collider);
}

void PhysicsTestObject::Start()
{
	GameObject::Start();

	transform->SetLocalPosition(glm::vec3(5, 0, 0));
	SetMeshRenderer(this->AddComponent<MeshRenderer>());
	//GetMeshRenderer()->SetMesh(cylinderMesh);
	//setMaterial(brickMat);
	transform->Scale(glm::vec3(1, 1, 1));
}

void PhysicsTestObject::Update(float timeStep)
{
	GameObject::Update(timeStep);
	

	float speed = 0.5;
	rigidbody->velocity = glm::vec2(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rigidbody->velocity.x = speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rigidbody->velocity.x = -speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		rigidbody->velocity.y = speed;
	}
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		 rigidbody->velocity.y = -speed;
	}
}
