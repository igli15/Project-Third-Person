#include "RigidBody.h"



RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::Start()
{
	//m_transform =;
	//m_collider  = m_gameObject->GetComponent<ColliderComponent>();
}

void RigidBody::Update(float timeStep)
{
	//FirstMove then resolve collision

	m_oldPos = m_gameObject->transform->LocalPosition();
	glm::vec3 velocity3d = glm::vec3(velocity.x, 0, velocity.y);

	m_gameObject->transform->Translate(velocity3d);
	m_collider->DetectCollision();

}

void RigidBody::SetCollider(ColliderComponent * collider)
{
	m_collider = collider;
}

void RigidBody::OnCollisionStay(CollisionInfo * collisionInfo)
{
	//Resolve Collision HERE
	std::cout << std::endl<< "RB STAY:" << std::endl;

	float vx = velocity.x;
	float vy = velocity.y;

	if (velocity.x == 0)  vx = 0.00001f;
	if (velocity.y == 0)  vy = 0.00001f;



	float ratio=glm::min(collisionInfo->distance.x / glm::abs(vx), collisionInfo->distance.y / glm::abs(vy));

	std::cout << "Distance: " << collisionInfo->distance << std::endl;
	std::cout << "Ratio: " << ratio << std::endl;
	glm::vec3 displacement = -glm::vec3(velocity.x, 0, velocity.y) * ratio;
	m_gameObject->transform->Translate(displacement);
	std::cout << "NewPos: " << m_gameObject->transform->LocalPosition() << std::endl;
	//velocity = velocity*-bounciness;

	//delete CollisionInfo
}
