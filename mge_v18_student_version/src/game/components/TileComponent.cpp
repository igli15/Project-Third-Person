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

void TileComponent::SetGridPos(glm::ivec2 gridPos)
{
	m_gridPos = gridPos;
}

glm::ivec2 TileComponent::GridPos()
{
	return m_gridPos;
}

bool TileComponent::IsPainted()
{
	return m_isPainted;
}

void TileComponent::SetTileType(TileType newType)
{
	m_tileType = newType;
}

TileType TileComponent::GetTileType()
{
	return m_tileType;
}

