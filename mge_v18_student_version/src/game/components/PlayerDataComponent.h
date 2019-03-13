#pragma once
#include "mge/core/XMLComponent.h"
#include "mge/core/CollisionInfo.h"
#include "mge/materials/TextureMaterial.hpp"
#include "game/components/TileComponent.h"
#include "SFML/System.hpp"
#include "mge/core/Tweener.h"

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

	GameObject* GetEnemy();
private:
	//PLayer id 1 or 2
	int m_playerNumber;
	//spawn position will be taken as position when Start() was called
	glm::vec3 m_spawnPosition;
	//Tween is needed for the death position animation
	tweeny::tween<float,float,float>* m_position_tween = nullptr;
	//Tween is needed for the death scale animation
	tweeny::tween<float, float, float>* m_scale_tween = nullptr;
	//Tween is needed for the falling of helmet
	tweeny::tween<float, float, float>* m_helmet_tween = nullptr;

	//
	//
	glm::vec3 tweenedVector;
	glm::vec3 tweenedScale;
	glm::vec3 tweenedHelmetPosition;

	sf::Clock m_respawnClock;

	sf::Clock m_blinkingClock;

	bool m_isDead = false;
	float m_respawnTime = 2;
	float m_penaltyTime = 0;
	float m_penaltyTimePerTile = 0.025f;

	float m_explosionWidth = 6;
	float m_explosionHeight = 6;

	GameObject* m_helmetObject;

	PlayerMovementComponent* m_playerMovement;
	ShootingComponent* m_shootingComponent;
	TileType m_tileMaterial;
	TextureMaterial* m_material;
	GridComponent* m_levelGrid;

	void StartDeathAnimation();

	void OnDestroy() override;
};

