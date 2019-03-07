#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/components/RigidBody.h"
#include "mge/core/CollisionInfo.h"
#include "game/components/GridComponent.h"

class PlayerDataComponent;

class PlayerMovementComponent :public XMLComponent
{
public:
	enum Direction { LEFT, RIGHT, FORWARD, BACKWARD,NONE };

	void Awake();
	void Start();
	void Update(float timeStep);
	//void OnCollision(CollisionInfo* collisionInfo);
	//void OnTrigger(CollisionInfo* collisionInfo);
	void SetPlayerNumber(int playerNumber);
	void SetArenaData(glm::vec2 pos, glm::vec2 size);
	void SetSpeed(float speed);

	Direction GetCurrentDirection();

	PlayerMovementComponent();
	virtual ~PlayerMovementComponent();


	virtual void Parse(rapidxml::xml_node<>* compNode) override;
private:
	Direction m_currentDirection;
	Direction m_oldFirection;

	RigidBody* m_rigidbody;
	int m_playerNumber;
	glm::vec2 m_arenaPosition;
	glm::vec2 m_arenaSize;
	PlayerDataComponent* m_playerData;
	GridComponent* m_grid;

	float m_speed = 0.1f;

	float m_initSpeed;
	float m_speedUpAmount = 1.0f;
	float m_slowDownAmount = 0.5f;

	void ApplyMovement(bool isMoved);
	void ApplyDirection();
	void SetRotation(glm::vec3 worldDirection, glm::vec3 localDirection);

};

