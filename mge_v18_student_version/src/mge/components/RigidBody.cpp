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
	float vx = (velocity.x == 0)? 0.00001f :velocity.x;
	float vy = (velocity.y == 0) ? 0.00001f : velocity.y;
	float ratio=glm::min(collisionInfo->distance.x / glm::abs(vx), collisionInfo->distance.y / glm::abs(vy));

	glm::vec3 displacement = -glm::vec3(velocity.x, 0, velocity.y) * ratio;
	m_gameObject->transform->Translate(displacement);

	//velocity = velocity*-bounciness;

	delete collisionInfo;
}
