#pragma once

#include "GridElement.h"

class PlayerDataComponent;

class CannonComponnet : GridElement
{
public:
	CannonComponnet();
	virtual ~CannonComponnet();


	virtual void OnPainted(PlayerDataComponent* playerData) override;

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

};

