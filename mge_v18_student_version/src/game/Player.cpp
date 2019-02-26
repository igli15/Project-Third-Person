#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::Load()
{
	m_circleCollider = AddComponent<CircleCollider>();
	m_rigidBody= AddComponent<RigidBody>();
	SetRigidBody(m_rigidBody);
	m_movementComponent = AddComponent<PlayerMovementComponent>();
	m_meshRenderer = AddComponent<MeshRenderer>();

	
}

void Player::Start()
{
	SetMeshRenderer(m_meshRenderer);

	m_movementComponent->SetPlayerNumber(1);

	m_circleCollider->radius = 1;
	m_circleCollider->AddCollisionFilterTag("walls");
	m_circleCollider->AddCollisionFilterTag("players");
	m_circleCollider->SetCollisionLayerTag("players");

	m_rigidBody->SetCollider(m_circleCollider);
	m_rigidBody->SetMaxSpeed(0.3f);

}

void Player::SetPlayerNumber(int playerNumber)
{
	m_movementComponent->SetPlayerNumber(playerNumber);
}
