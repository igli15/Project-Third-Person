#pragma once
#include "mge/core/Component.h"
#include "mge/components/RigidBody.h"
#include "mge/core/CollisionInfo.h"

class PlayerMovementComponent :public Component
{
public:
	enum Direction {LEFT,RIGHT,FORWARD,BACKWARD};
	Direction currentDirection;

	void Awake();
	void Start();
	void Update(float timeStep);
	void OnCollision(CollisionInfo* collisionInfo);

	void SetPlayerNumber(int playerNumber);
	void SetArenaData(glm::vec2 pos, glm::vec2 size);
	PlayerMovementComponent();
	virtual ~PlayerMovementComponent();
private:
	RigidBody* m_rigidbody;
	int m_playerNumber;
	glm::vec2 m_arenaPosition;
	glm::vec2 m_arenaSize;

	bool IsOutOfBorder();

};

