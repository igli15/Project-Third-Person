#include "RigidBody.h"

#include "CircleCollider.h"
#include "ColliderComponent.hpp"
#include "RectangleCollider.h"

RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Start()
{
	Component::Start();
	RigidBody* rb= m_gameObject->GetRigidBody();
	m_collider = m_gameObject->GetComponent<ColliderComponent>();
}

void RigidBody::Update(float timeStep)
{
	//FirstMove then resolve collision
	m_oldPos = m_gameObject->transform->LocalPosition();

	velocity += m_acceleration - m_friction * velocity;
	
	//set max length of velocity
	


	if (glm::length(velocity) >= m_maxSpeed)
	{
		velocity = glm::normalize(velocity) * m_maxSpeed;
	}

	glm::vec3 velocity3d = glm::vec3(velocity.x, 0, velocity.y);
	//std::cout << "pos: " << m_gameObject->transform->LocalPosition() << m_gameObject->ID()<< std::endl;

	m_gameObject->transform->SetLocalPosition(m_gameObject->transform->LocalPosition() + velocity3d);
	m_collider->DetectCollision();

}

void RigidBody::SetCollider(ColliderComponent * collider)
{
	m_collider = collider;
}

ColliderComponent * RigidBody::GetCollider()
{
	return m_collider;
}

void RigidBody::OnCollisionStay(CollisionInfo * collisionInfo)
{
	//std::cout << "COLLISION" << std::endl;
	//float vx = (velocity.x == 0)? 0.1f :velocity.x;
	//loat vy = (velocity.y == 0) ? 0.1f : velocity.y;

	//float ratio=glm::min(collisionInfo->distance.x, collisionInfo->distance.y);

	//if (ratio > 1) ratio = 1;
	//if (ratio < 0.01f) ratio = 0.01f;
	//glm::vec3 displacement =   glm::vec3(collisionInfo->normal.x, 0, collisionInfo->normal.y) * ratio;

	//std::cout << std::endl;
	//std::cout << "RATIO: " << ratio << std::endl;
	//std::cout << "Depth: " << collisionInfo->distance << std::endl;
	//std::cout << "velocity: " << velocity << std::endl;
	//std::cout << "Normal" << glm::vec3(collisionInfo->normal.x, 0, collisionInfo->normal.y) << std::endl;
	//std::cout << "Displacement: " << displacement << std::endl;

	//velocity = glm::vec2(0, 0);
	velocity = collisionInfo->normal*bounciness;
	SetAcceleration(glm::vec2(0, 0));

	//m_gameObject->transform->Translate(displacement);

	//Parsing collisionInfo to gameobject
	m_gameObject->OnCollision(collisionInfo);
	//Making sure to clear CollisionInfo in the end
	delete collisionInfo;
}

void RigidBody::SetAcceleration(glm::vec2 a)
{
	m_acceleration = a;
}

void RigidBody::SetMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

glm::vec2 RigidBody::GetAcceleration()
{
	return m_acceleration;
}

float RigidBody::GetMaxSpeed()
{
	return m_maxSpeed;
}

void RigidBody::Parse(rapidxml::xml_node<>* compNode)
{
	for (rapidxml::xml_attribute<>* a = compNode->first_attribute();
		a != nullptr;
		a = a->next_attribute())
	{
		std::string attributeName = a->name();

		if (attributeName == "friction")
		{
			m_friction = strtof(a->value(), 0);
		}
		else if (attributeName == "maxSpeed")
		{
			m_maxSpeed = strtof(a->value(), 0);
		}
		else if (attributeName == "bounciness")
		{
			bounciness = strtof(a->value(), 0);
		}
		
	}
}
