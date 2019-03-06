#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/core/CollisionInfo.h"
#include "mge/materials/TextureMaterial.hpp"
#include "game/components/TileComponent.h"
#include "SFML/System.hpp"

class PlayerMovementComponent;
class ShootingComponent;
class GridComponent;

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

	void OnDeath();
	void Respawn();

	void SetSpawnPosition(glm::vec3 newSpawnPosition);
	void SetCurrentPositionAsSpawnPosisition();
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	TileType MatType();
	bool IsDead();
private:
	//PLayer id 1 or 2
	int m_playerNumber;
	//spawn position will be taken as position when Start() was called
	glm::vec3 m_spawnPosition;

	sf::Clock m_respawnClock;
	bool m_isDead = false;
	float m_respawnTime = 2;
	float m_penaltyTime = 0;
	float m_maxPenaltyTime = 20;

	PlayerMovementComponent* m_playerMovement;
	ShootingComponent* m_shootingComponent;
	TileType m_tileMaterial;
	TextureMaterial* m_material;
	GridComponent* m_levelGrid;
};

