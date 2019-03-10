#pragma once
#include "mge/core/XMLComponent.h"
#include "SFML/System.hpp"
#include "tweeny/tweeny.h"

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
	void SetInkLevel(float newInkLevel);
	void ResetInkLevel();

	void OnKeyPressed(bool isKeyPressedThisFrame);
	void OnKeyEnter();
	void OnKeyStay();
	void OnKeyExit();
private:
	PlayerMovementComponent* m_playerMovementComponent;
	GridComponent* m_gridComponent;
	sf::Clock m_clock;

	int m_inkMaxLevel = 100;
	float m_inkLevel = 100;

	bool m_isChraging = false;

	float m_currentAmmo=0;
	int m_minRange = 2;
	int m_maxRange = 6;

	float m_rateOfGainInk = 0.1f;

	int m_playerNumber = 1;

	bool m_isKeyPresedLastFrame=false;

	tweeny::tween<int>* testTween;
};

