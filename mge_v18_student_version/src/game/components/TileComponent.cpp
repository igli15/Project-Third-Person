#include "TileComponent.h"



TileComponent::TileComponent()
{
}


TileComponent::~TileComponent()
{
}

void TileComponent::Parse(rapidxml::xml_node<>* compNode)
{
}

void TileComponent::SetGridPos(glm::vec2 gridPos)
{
	m_gridPos = gridPos;
}

glm::vec2 TileComponent::GridPos()
{
	return m_gridPos;
}

