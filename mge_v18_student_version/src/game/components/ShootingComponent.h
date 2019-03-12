#pragma once
#include "mge/core/XMLComponent.h"
#include "SFML/System.hpp"
#include "tweeny/tweeny.h"
#include "game/components/KeyObject.h"

class PlayerDataComponent;
class PlayerMovementComponent;
class GridComponent;
class TileComponent;

class ShootingComponent : public XMLComponent
{
public:
	ShootingComponent();
	virtual ~ShootingComponent();

	void Start() override;
	void Update(float timeStep) override;

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void ShootInk(float tileAmount, bool isPrimaryShooting);
	void SetPlayerNumber(int playerNumber);
	void SetGrid(GridComponent* grid);
	void SetInkLevel(float newInkLevel);
	void ResetInkLevel();
	void AddInk(float inkLevel);

	void OnKeyOneEnter();
	void OnKeyOneStay();
	void OnKeyOneExit();

	void OnKeyTwoEnter();
	void OnKeyTwoStay();
	void OnKeyTwoExit();

private:
	KeyObject* keyOne;
	KeyObject* keyTwo;

	PlayerMovementComponent* m_playerMovementComponent;
	GridComponent* m_gridComponent;
	sf::Clock m_clock1;
	sf::Clock m_clock2;

	PlayerDataComponent* m_playerDataCompoent;
	float m_reloadTime1 = 0.5f;
	float m_relaodTime2 = 1;

	std::vector<TileComponent*> m_selectedTiles;

	int m_inkMaxLevel = 100;
	float m_inkLevel = 0;

	bool m_isChraging = false;

	float m_currentAmmo=0;
	int m_minRange = 2;
	int m_maxRange = 6;

	float m_rateOfGainInk = 0.1f;

	int m_playerNumber = 1;

	bool m_isKeyPresedLastFrame=false;
	
};

