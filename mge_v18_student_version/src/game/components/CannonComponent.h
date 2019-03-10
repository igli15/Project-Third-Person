#pragma once

#include "GridElement.h"

class PlayerDataComponent;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class CannonComponent : public GridElement
{

public:
	CannonComponent();
	virtual ~CannonComponent();

	virtual void OnPainted(PlayerDataComponent* playerData) override;

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

	void Start() override;

private:
	int m_shootingRange = 6;

	Direction m_facingDir;

	
};

