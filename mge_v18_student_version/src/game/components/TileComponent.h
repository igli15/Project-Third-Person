#pragma once
#include "mge/core/XMLComponent.h"
#include "glm.hpp"

class TileComponent : public XMLComponent
{
public:
	TileComponent();
	virtual ~TileComponent();

	void Parse(rapidxml::xml_node<>* compNode) override;

	void SetGridPos(glm::ivec2 gridPos);
	glm::ivec2 GridPos();

private:
	glm::ivec2 m_gridPos;
};

