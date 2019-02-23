#include "GridComponent.h"
#include "game/components/TileComponent.h"


GridComponent::GridComponent()
{
}


GridComponent::~GridComponent()
{
}

void GridComponent::SetWidth(int width)
{
	m_width = width;
}

void GridComponent::SetHeight(int height)
{
	m_height = height;
}

void GridComponent::SetTileRadius(int r)
{
	m_tileRadius = r;
}

int GridComponent::Width() const
{
	return m_width;
}

int GridComponent::Height() const
{
	return m_height;
}

int GridComponent::TileRadius() const
{
	return m_tileRadius;
}

void GridComponent::AddTile(TileComponent * tile)
{
	for (int i = 0; i < m_height; i++)
	{
		if (m_tileGrid[m_height].size() < m_width)
		{
			m_tileGrid[m_height].push_back(tile);
		}
	}
}

void GridComponent::Parse(rapidxml::xml_node<>* compNode)
{
}
