#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/components/RigidBody.h"
#include "mge/core/CollisionInfo.h"

class PlayerMovementComponent :public XMLComponent
{
public:
	enum Direction { LEFT, RIGHT, FORWARD, BACKWARD };

	void Awake();
	void Start();
	void Update(float timeStep);
	void OnCollision(CollisionInfo* collisionInfo);

	void SetPlayerNumber(int playerNumber);
	void SetArenaData(glm::vec2 pos, glm::vec2 size);
	void SetSpeed(float speed);

	Direction GetCurrentDirection();

	PlayerMovementComponent();
	virtual ~PlayerMovementComponent();

	virtual void Parse(rapidxml::xml_node<>* compNode) override;
private:
	Direction m_currentDirection;
	RigidBody* m_rigidbody;
	int m_playerNumber;
	glm::vec2 m_arenaPosition;
	glm::vec2 m_arenaSize;

	float m_speed = 0.1f;
	bool IsOutOfBorder();
	void SetRotation(glm::vec3 worldDirection, glm::vec3 localDirection);

};

