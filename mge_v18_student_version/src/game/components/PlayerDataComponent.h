#pragma once
#include "mge/core/Component.h"
#include "mge/core/CollisionInfo.h"

class PlayerDataComponent : public Component
{
public:
	PlayerDataComponent();
	virtual ~PlayerDataComponent();

	void Start();
	void Update(float timeStep);
	void OnCollision(CollisionInfo* collisionInfo);

	void SetPlayerNumber(int playerNumber);
	int  GetPlayerNumber();

	void RespawnPlayer();
	void SetSpawnPosition(glm::vec3 newSpawnPosition);
	void SetCurrentPositionAsSpawnPosisition();
private:
	//PLayer id 1 or 2
	int m_playerNumber;
	//spawn position will be taken as position when Start() was called
	glm::vec3 m_spawnPosition;
};

