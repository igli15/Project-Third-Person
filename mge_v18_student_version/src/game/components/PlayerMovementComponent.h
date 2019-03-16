#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/components/RigidBody.h"
#include "mge/core/CollisionInfo.h"
#include "game/components/GridComponent.h"
#include "game/components/KeyObject.h"
class PlayerDataComponent;

class PlayerMovementComponent :public XMLComponent
{
public:
	enum Direction { LEFT, RIGHT, FORWARD, BACKWARD,NONE };
	Direction GetCurrentDirection();

	void Awake();
	void Start();
	void Update(float timeStep);
	void SetPlayerNumber(int playerNumber);
	void SetArenaData(glm::vec2 pos, glm::vec2 size);
	void SetSpeed(float speed);

	PlayerMovementComponent();

	virtual ~PlayerMovementComponent();
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

private:
	KeyObject* keyLeft;
	KeyObject* keyRight;
	KeyObject* keyForward;
	KeyObject* keyBackward;

	Direction m_currentDirection;
	Direction m_oldDirection;
	PlayerDataComponent* m_playerData;
	GridComponent* m_grid;
	RigidBody* m_rigidbody;

	glm::vec2 m_arenaPosition;
	glm::vec2 m_arenaSize;

	int m_playerNumber;

	float m_speed = 0.1f;
	float m_initSpeed;
	float m_speedUpAmount = 1.0f;
	float m_slowDownAmount = 0.5f;

	bool isAnyKeyReleased = false;

	void OnEnterHorizontal(int direction);
	void OnEnterVertical(int direction);

	void OnStayHorizontal(int direciton);
	void OnStayVertical(int direction);

	void OnExitHorizontal(int direciton);
	void OnExitVertical(int direction);

	void ApplyMovement(bool isMoved);
	void ApplyDirection();
	void SetRotation(glm::vec3 worldDirection, glm::vec3 localDirection);

};

