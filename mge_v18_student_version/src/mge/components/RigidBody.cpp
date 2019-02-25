#include "RigidBody.h"



RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Start()
{
	m_gameObject->SetRigidBody(this);
	//m_transform =;
	//m_collider  = m_gameObject->GetComponent<ColliderComponent>();
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

	m_gameObject->transform->Translate(velocity3d);
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

	float vx = (velocity.x == 0)? 0.00001f :velocity.x;
	float vy = (velocity.y == 0) ? 0.00001f : velocity.y;

	float ratio=glm::min(collisionInfo->distance.x / glm::abs(vx), collisionInfo->distance.y / glm::abs(vy));
	if (ratio > 1) ratio = 1;
	glm::vec3 displacement = -glm::vec3(velocity.x, 0, velocity.y) * ratio;

	velocity = glm::vec2(0, 0);
	SetAcceleration(glm::vec2(0, 0));

	//std::cout << std::endl;
	//std::cout << "Ratio X: " << collisionInfo->distance.x / glm::abs(vx) << std::endl;
	//std::cout << "Ratio Y: " << collisionInfo->distance.y / glm::abs(vy) << std::endl;
	//std::cout << "Displacement: " << displacement << std::endl;

	m_gameObject->transform->Translate(displacement);


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