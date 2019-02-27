#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/core/CollisionInfo.h"

class PlayerDataComponent : public XMLComponent
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
	virtual void Parse(rapidxml::xml_node<>* compNode) override;
private:
	//PLayer id 1 or 2
	int m_playerNumber;
	//spawn position will be taken as position when Start() was called
	glm::vec3 m_spawnPosition;

};

