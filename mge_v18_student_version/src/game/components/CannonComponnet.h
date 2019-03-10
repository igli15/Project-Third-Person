#pragma once

#include "GridElement.h"

class CannonComponnet : GridElement
{
public:
	CannonComponnet();
	virtual ~CannonComponnet();


	virtual void OnPainted(TileType type);

	// Inherited via XMLComponent
	virtual void Parse(rapidxml::xml_node<>* compNode) override;

};

