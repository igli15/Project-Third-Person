#pragma once
#include "mge/core/XMLComponent.h"
#include "glm.hpp"

class TileComponent : public XMLComponent
{
public:
	TileComponent();
	virtual ~TileComponent();

	void Parse(rapidxml::xml_node<>* compNode) override;

	void SetGridPos(glm::vec2 gridPos);
	glm::vec2 GridPos();

private:
	glm::vec2 m_gridPos;
};

