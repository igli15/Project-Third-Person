#pragma once
#include "mge/core/XMLComponent.h"

class PlayerMovementComponent;
class GridComponent;

class ShootingComponent : public XMLComponent
{
public:
	ShootingComponent();
	virtual ~ShootingComponent();

	void Start() override;
	void Update(float timeStep) override;

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void ShootInk(float tileAmount);
	void SetPlayerNumber(int playerNumber);
	void SetGrid(GridComponent* grid);

private:
	PlayerMovementComponent* m_playerMovementComponent;
	GridComponent* m_gridComponent;

	float m_inkMaxLevel = 100;
	float m_inkLevel = 100;

	float m_reloadTime = 2;
	float m_lastShotTime = 0;
	int m_playerNumber = 1;
	float m_shootingRange = 2;
};

