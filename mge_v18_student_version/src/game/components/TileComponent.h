#pragma once
#include "mge/core/XMLComponent.h"


class TileComponent : public XMLComponent
{
public:
	TileComponent();
	virtual ~TileComponent();

	void Parse(rapidxml::xml_node<>* compNode) override;
};

