#pragma once
#include "mge/core/XMLComponent.h"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class TileComponent;

class BallonSpawnerComponent : public XMLComponent
{
public:
	BallonSpawnerComponent();
	virtual ~BallonSpawnerComponent();

	void Start() override;

	void Update(float timeStep);

	void OnDestroy() override;

	void SpawnBalloon();

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

private:
	sf::Clock m_balloonSpawnClock;

	float m_balloonSpawnTime = 3;

	TileComponent* m_parentTile = nullptr;

	bool m_spawnOnStart = false;
	
};

